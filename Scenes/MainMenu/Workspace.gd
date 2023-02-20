# MainMenu/Workspace.gd

extends Panel

# Signals
signal start_analyze(chord: TargetChord)
signal stop_analyze

# Exported variables
@export_range(0.0, 10.0) var sidebar_swiftness: float = 0.8

# GUI variables
var is_dragging: bool = false
var can_drag: bool = true
var dragging_ralative: Vector2
var dragging_distance: float

# Variables
var chords_arr: Array
var keys: Array[int]
## Alternation is how much pairs in one key
var iter_max: int
var iter_cur: int
var cur_key_idx: int
var cur_chord_idx: int

# MARK: - Onready variables

@onready var sidebar: Panel = $SideBar
@onready var sidebar_close: Button = $SideBar/Close
@onready var ranks: Button = $RankHistoryButton
@onready var start: Button = $StartButton
@onready var to_next: Button = $ToNextButton
@onready var finish: Button = $FinishButton
@onready var values_label: Control = $ValuesLabel
@onready var chord_view: Control = $ChordView
@onready var complexity_level: Control = $ComplexityLevel
@onready var current_key: Label = $CurrentKey
@onready var tween: Tween
@onready var countdown: PackedScene = load("res://Resources/UIElements/CountDown/CountDown.tscn")
@onready var generator: Neck = Neck.new()

func _ready() -> void:
	GlobalVars.main_scene_workspace = self
	set_process(false)
	call_deferred("connect_signals")
	hide_sidebar()

## Connecting input signals
func connect_signals() -> void:
	sidebar_close.pressed.connect(hide_sidebar)
	ranks.pressed.connect(show_sidebar)
	start.pressed.connect(start_exercise)
	to_next.pressed.connect(handle_to_next_pressed)
	finish.pressed.connect(execute_finish)
	get_viewport().size_changed.connect(handle_changing_window_size)
	GlobalVars.audio_analyzer.analyze_ready.connect(execute_success)

# MARK: - sidebar functions

## Handle drag on touchscreen (or mouse) for sidebar
func _input(event: InputEvent) -> void:
	if event is InputEventScreenDrag and can_drag:
		handle_screen_drag(event)
	elif event is InputEventScreenTouch and is_dragging:
		handle_release(event)

## Handle animation closing sidebar
func hide_sidebar() -> void:
	if tween and tween.is_valid(): return
	tween = get_tree().create_tween()
	var tweener: Tweener = tween.tween_property(sidebar, "sidebar_pos",
			Vector2(sidebar.x_max, sidebar.sidebar_pos.y), sidebar_swiftness)
	tweener.set_trans(Tween.TRANS_CUBIC).set_ease(Tween.EASE_OUT)

## Handle animation opening sidebar
func show_sidebar() -> void:
	if tween and tween.is_valid(): return
	tween = get_tree().create_tween()
	var tweener: Tweener = tween.tween_property(sidebar, "sidebar_pos",
			Vector2(sidebar.x_min, sidebar.sidebar_pos.y), sidebar_swiftness)
	tweener.set_trans(Tween.TRANS_CUBIC).set_ease(Tween.EASE_OUT)

## Detect start drag direction and process it
func handle_screen_drag(event: InputEventScreenDrag) -> void:
	if tween and tween.is_valid(): return
	if not is_dragging:
		dragging_distance = event.position.x - sidebar.sidebar_pos.x
	is_dragging = true
	dragging_ralative = event.relative
	var win_siz: float = DisplayServer.window_get_size().x
	var sid_pos: Vector2 = sidebar.sidebar_pos
	var drag_pos: float = event.position.x
	var region: float = win_siz - ((win_siz - sid_pos.x) + 200.0)
	if (drag_pos > region):
		sidebar.sidebar_pos = Vector2(drag_pos - dragging_distance, sid_pos.y)
	else: is_dragging = false
	get_viewport().set_input_as_handled()

## Process drag release and finishing animation
func handle_release(event: InputEventScreenTouch) -> void:
	if not event.pressed:
		is_dragging = false
		sidebar.finalize_motion(tween, dragging_ralative, sidebar_swiftness)

## We need to update constrains on sidebar on window's size changing
func handle_changing_window_size() -> void:
	sidebar.update_constrains()

# MARK: - exercise loop

func lets_countdown() -> void:
	var child: Control = countdown.instantiate()
	add_sibling(child)
	await child.countdown_finished
	get_parent().remove_child(child)

func prepare_ex_begin() -> void:
	# Temp gui disabling
	start.hide()
	complexity_level.hide()
	hide_sidebar()
	ranks.disabled = true
	can_drag = false

	# Little pause
	#await lets_countdown()

	# Temp gui showing
	to_next.show()
	to_next.disabled = false
	to_next.grab_focus()
	finish.show()
	current_key.show()

func prepare_ex_end() -> void:
	pass

## Handle pressing "Start" button and starting exercise.
func start_exercise() -> void:
	keys = Utils.get_keys_for_cpp()
	iter_max = Utils.get_alternation()
	iter_cur = 0
	keys.shuffle()
	cur_key_idx = 0
	prepare_ex_begin()
	run_cycle()

func run_cycle() -> void:
	# Rules of exiting from cycle
	if iter_cur >= iter_max and cur_key_idx < keys.size() - 1:
		cur_key_idx += 1
		iter_cur = 0
	elif iter_cur >= iter_max and cur_key_idx >= keys.size() - 1:
		execute_finish()
		return
	iter_cur += 1

	#Set chords counter to zero
	cur_chord_idx = 0

	# Values cycle
	var values: Dictionary = generator.get_values()
	values_label.set_values(values)

	# Update scene views, before next iteration
	chord_view.hide()
	values_label.show()
	current_key.text = "Current key: " + Utils.int_to_key_s(keys[cur_key_idx])

	# Wee need to know beforehand, if we got 2'nd string, there are no
	# chords, and button's text needs to be "NEXT" instead of "TO CHORDS"
	chords_arr = generator.get_chords(keys[cur_key_idx], GlobalSettings.is_modern)
	if chords_arr.is_empty():
		to_next.text = "NEXT"
	else:
		to_next.text = "TO CHORDS"

## Called by pressing button, starts new degree-string iteration
func handle_to_next_pressed() -> void:
	# Activate chord sub-iteration
	if to_next.text == "TO CHORDS":
		to_next.text = "SKIP"
		values_label.hide()
		chord_view.show()
		show_next_chord()
	# Next iteration
	elif to_next.text == "NEXT":
		run_cycle()
	elif to_next.text == "SKIP":
		emit_signal("stop_analyze")

func get_next_chord() -> TargetChord:
	if chords_arr.is_empty() or cur_chord_idx >= chords_arr.size():
		return null
	var ret: TargetChord = chords_arr[cur_chord_idx]
	cur_chord_idx += 1
	# Check if it is last iteration
	if iter_cur + 1 >= iter_max and \
		cur_key_idx >= keys.size() - 1 and \
		cur_chord_idx >= chords_arr.size():
			to_next.disabled = true
	return ret

## Prepare and show chords in the exercise iteration
func show_next_chord() -> void:
	var chord := get_next_chord()
	if chord == null:
		run_cycle()
		return
	
	chord_view.init_view(chord.get_chord_name())
	emit_signal("start_analyze", chord)
					
func execute_success() -> void:
	chord_view.success()
	await chord_view.finish_view
	show_next_chord()
	
## Finish the exercise
func execute_finish() -> void:
	to_next.text = "NEXT"
	chord_view.hide()
	ranks.set_disabled(false)
	can_drag = true
	values_label.hide()
	to_next.hide()
	current_key.hide()
	finish.hide()
	start.show()
	complexity_level.show()

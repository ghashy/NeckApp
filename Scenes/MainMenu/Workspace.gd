# MainMenu/Workspace.gd

extends Panel

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

@onready var start: Button = $StartButton
@onready var to_next: Button = $ToNextButton
@onready var finish: Button = $FinishButton
@onready var values_label: Control = $ValuesLabel
@onready var complexity_level: Control = $ComplexityLevel
@onready var current_key: Label = $CurrentKey
@onready var tween: Tween
@onready var countdown: PackedScene = load("res://Resources/UIElements/CountDown/CountDown.tscn")
@onready var generator: Generator = Generator.new()

func _ready() -> void:
	set_process(false)
	call_deferred("connect_signals")

## Connecting input signals
func connect_signals() -> void:
	start.pressed.connect(start_exercise)
	to_next.pressed.connect(handle_to_next_pressed)
	finish.pressed.connect(execute_finish)

# EXERCISE LOOP

func lets_countdown() -> void:
	var child: Control = countdown.instantiate()
	add_sibling(child)
	await child.countdown_finished
	get_parent().call_deferred("remove_child", child)

func prepare_ex_begin() -> void:
	# Temp gui disabling
	start.hide()
	complexity_level.hide()
	can_drag = false

	# Little pause
	await lets_countdown()

	# Temp gui showing
	to_next.show()
	to_next.disabled = false
	to_next.grab_focus()
	finish.show()
	current_key.show()

## Handle pressing "Start" button and starting exercise.
func start_exercise() -> void:
	keys = Utils.get_keys_for_cpp()
	iter_max = Utils.get_alternation()
	iter_cur = 0
	keys.shuffle()
	cur_key_idx = 0
	await prepare_ex_begin()
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

	# Values cycle
	var values: Dictionary = generator.get_values()
	values_label.set_values(values)

	# Update scene views, before next iteration
	values_label.show()
	current_key.text = "Current key: " + Utils.int_to_key_s(keys[cur_key_idx])

## Called by pressing button, starts new degree-string iteration
func handle_to_next_pressed() -> void:
	run_cycle()

## Finish the exercise
func execute_finish() -> void:
	to_next.text = "NEXT"
	can_drag = true
	values_label.hide()
	to_next.hide()
	current_key.hide()
	finish.hide()
	start.show()
	complexity_level.show()

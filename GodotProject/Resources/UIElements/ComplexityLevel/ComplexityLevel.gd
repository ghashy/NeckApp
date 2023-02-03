# ComplexityLevel.gd

extends Control

# Onready variables
@onready var selected_keys_popup: PopupMenu = $VBox/Keys.get_popup()
@onready var selected_alt_popup: PopupMenu = $VBox/Alternation.get_popup()
@onready var checked_items: Dictionary = \
									GlobalSettings.keys_selected_values

##------------------------------------------------------------------------------

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	set_process(false)
	init_keys_and_alts()

##------------------------------------------------------------------------------

func handle_keys_pressed(index: int) -> void:
	selected_keys_popup.toggle_item_checked(index)
	var is_checked: bool = selected_keys_popup.is_item_checked(index)
	var key: String = selected_keys_popup.get_item_text(index)
	if key == "Select ALL" or key == "Unselect ALL":
		for i in selected_keys_popup.item_count:
			selected_keys_popup.set_item_checked(i, is_checked)
			checked_items[selected_keys_popup.get_item_text(i)] = is_checked
		# Handle interface changes
		if is_checked:
			selected_keys_popup.set_item_text(index, "Unselect ALL")
		else:
			selected_keys_popup.set_item_text(index, "Select ALL")
		
		GlobalSettings.save_settings()
		return
	checked_items[selected_keys_popup.get_item_text(index)] = is_checked
	GlobalSettings.save_settings()

##------------------------------------------------------------------------------

func handle_alts_pressed(index: int) -> void:
	for i in selected_alt_popup.item_count:
		selected_alt_popup.set_item_checked(i, false)
	selected_alt_popup.set_item_checked(index, true)
	GlobalSettings.alternation_selected_value = index
	GlobalSettings.save_settings()

##------------------------------------------------------------------------------

func init_keys_and_alts() -> void:
	selected_keys_popup.set_hide_on_checkable_item_selection(false)
	selected_keys_popup.index_pressed.connect(handle_keys_pressed)
	selected_alt_popup.index_pressed.connect(handle_alts_pressed)

	# Setup selected keys.
	for i in selected_keys_popup.item_count:
		selected_keys_popup. \
		set_item_checked(i, checked_items[selected_keys_popup.get_item_text(i)])
	
	# Setup selected alternation.
	for i in selected_alt_popup.item_count:
		selected_alt_popup.set_item_checked(i, false)
	var index: int = GlobalSettings.alternation_selected_value
	selected_alt_popup.set_item_checked(index, true)

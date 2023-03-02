# Root.gd

extends Control

# Variables
var is_settings_opened: bool = false

# Onready variables
@onready var toggle_settings: Button = $SettingsButton
@onready var audio_graphic_layer: Control = $AudioGraphicLayer
@onready var dummy: Node = $Dummy

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	OS.set_low_processor_usage_mode(true)
	OS.set_low_processor_usage_mode_sleep_usec(13800)
	toggle_settings.pressed.connect(open_or_close_settings)
	DisplayServer.call_deferred("window_set_min_size", Vector2i(1280, 720))
	set_process(false)

func _process(delta: float) -> void:
	pass

func open_or_close_settings() -> void:
	if is_settings_opened:
		for child in self.get_children():
			if child.name == "settings":
				remove_child(child)
				child.queue_free()
		toggle_settings.set_text("SETTINGS")
	else:
		var settings_window: Control = \
			load("res://Scenes/SettingsWindow/SettingsWindow.tscn").instantiate()
		settings_window.name = "settings"
		dummy.add_sibling(settings_window)
		toggle_settings.set_text("BACK")
	is_settings_opened = not is_settings_opened

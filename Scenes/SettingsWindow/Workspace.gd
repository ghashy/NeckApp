# SettingsWindow/Workspace.gd

extends Panel

# Should use GlobalSettings singleton

# Onready variables
@onready var enable_fx: CheckButton = $VBox/ToggleAudioFX
@onready var enable_modern_naming: CheckButton = $VBox/IsModernNaming

func _ready() -> void:
	init_parameters()
	connect_signals()

func connect_signals() -> void:
	enable_fx.pressed.connect(toggle_fx)
	enable_modern_naming.pressed.connect(toggle_modern_naming_style)

func init_parameters() -> void:
	var is_fx_enabled: bool = GlobalSettings.is_sound_fx_enabled
	enable_fx.set_pressed_no_signal(is_fx_enabled)
	
	var is_modern_naming: bool = GlobalSettings.is_modern
	enable_modern_naming.set_pressed_no_signal(is_modern_naming)

func toggle_fx() -> void:
	GlobalSettings.is_sound_fx_enabled = enable_fx.is_pressed()
	GlobalSettings.save_settings()

func toggle_modern_naming_style() -> void:
	GlobalSettings.is_modern = enable_modern_naming.is_pressed()
	GlobalSettings.save_settings()

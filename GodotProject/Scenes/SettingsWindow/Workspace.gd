# SettingsWindow/Workspace.gd

extends Panel

# Should use GlobalSettings singleton

# Onready variables
@onready var enable_fx: CheckButton = $VBox/ToggleAudioFX
@onready var audio_btn: CheckButton = $VBox/ToggleInput
@onready var enable_modern_naming: CheckButton = $VBox/IsModernNaming
@onready var audio_driver: LineEdit = $VBox/SettingsList/HBox/VBox/AudioDriver
@onready var sample_rate_edit: LineEdit = $VBox/SettingsList/HBox/VBox/SampleRate
@onready var audio_output_list: OptionButton = $VBox/SettingsList/HBox/VBox/AudioOutput
@onready var audio_input_list: OptionButton = $VBox/SettingsList/HBox/VBox/AudioInput

##------------------------------------------------------------------------------

func _ready() -> void:
	init_output_device_list()
	init_input_device_List()
	init_parameters()
	connect_signals()

##------------------------------------------------------------------------------

func connect_signals() -> void:
	enable_fx.pressed.connect(toggle_fx)
	audio_btn.pressed.connect(toggle_audio)
	enable_modern_naming.pressed.connect(toggle_modern_naming_style)
	audio_driver.text_submitted.connect(save_driver_name)
	sample_rate_edit.text_submitted.connect(save_sample_rate)
	audio_output_list.item_selected.connect(save_output)
	audio_input_list.item_selected.connect(save_input)

##------------------------------------------------------------------------------

func init_output_device_list() -> void:
	for device in AudioServer.get_output_device_list():
		audio_output_list.get_popup().add_item(device)

##------------------------------------------------------------------------------

func init_input_device_List() -> void:
	for device in AudioServer.get_input_device_list():
		audio_input_list.get_popup().add_item(device)

##------------------------------------------------------------------------------

func init_parameters() -> void:
	var is_fx_enabled: bool = GlobalSettings.is_sound_fx_enabled
	enable_fx.set_pressed_no_signal(is_fx_enabled)
	
	var is_modern_naming: bool = GlobalSettings.is_modern
	enable_modern_naming.set_pressed_no_signal(is_modern_naming)
	
	var is_enabled: bool = ProjectSettings.get_setting("audio/driver/enable_input")
	audio_btn.set_pressed_no_signal(is_enabled)
	
	var driver: String = ProjectSettings.get_setting("audio/driver/driver")
	audio_driver.set_text(driver)
	
	var output: String = GlobalSettings.audio_output
	audio_output_list.set_text(output)
	AudioServer.set_output_device(output)
	
	var input: String = GlobalSettings.audio_input
	audio_input_list.set_text(input)
	AudioServer.set_input_device(input)
	
	var rate: String = str(ProjectSettings.get_setting("audio/driver/mix_rate"))
	sample_rate_edit.set_text(rate)

##------------------------------------------------------------------------------

func toggle_audio() -> void:
	ProjectSettings.set_setting("audio/driver/enable_input", audio_btn.is_pressed())
	GlobalSettings.save_project()
	

##------------------------------------------------------------------------------

func toggle_fx() -> void:
	GlobalSettings.is_sound_fx_enabled = enable_fx.is_pressed()
	GlobalSettings.save_settings()

##------------------------------------------------------------------------------

func toggle_modern_naming_style() -> void:
	GlobalSettings.is_modern = enable_modern_naming.is_pressed()
	GlobalSettings.save_settings()
##------------------------------------------------------------------------------

func save_driver_name(new_name: String) -> void:
	ProjectSettings.set_setting("audio/driver/driver", new_name)
	GlobalSettings.save_project()

##------------------------------------------------------------------------------

func save_sample_rate(new_rate: String) -> void:
	ProjectSettings.set_setting("audio/driver/mix_rate", new_rate.to_int())
	GlobalSettings.save_project()

##------------------------------------------------------------------------------

func save_output(idx: int) -> void:
	GlobalSettings.audio_output = audio_output_list.get_item_text(idx)
	AudioServer.set_output_device(audio_output_list.get_item_text(idx))
	GlobalSettings.save_settings()

##------------------------------------------------------------------------------

func save_input(idx: int) -> void:
	GlobalSettings.audio_input = audio_input_list.get_item_text(idx)
	AudioServer.set_input_device(audio_input_list.get_item_text(idx))
	GlobalSettings.save_settings()


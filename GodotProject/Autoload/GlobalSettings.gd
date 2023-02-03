# GlobalSettings.gd

extends Node

# Variables
var fs: FSIntervace
var is_sound_fx_enabled: bool
var audio_output: String
var audio_input: String
var keys_selected_values: Dictionary = {}
var alternation_selected_value: int
var is_modern: bool

##------------------------------------------------------------------------------

func _ready() -> void:
	set_process(false)
	fs = FSIntervace.new()
	init_settings()
	init_dictionary_values()
	fs.load_settings()

##------------------------------------------------------------------------------

func init_dictionary_values() -> void:
	keys_selected_values["E"] = true
	keys_selected_values["F"] = false
	keys_selected_values["F#"] = false
	keys_selected_values["G"] = false
	keys_selected_values["G#"] = false
	keys_selected_values["A"] = false
	keys_selected_values["B"] = false
	keys_selected_values["H"] = false
	keys_selected_values["C"] = false
	keys_selected_values["C#"] = false
	keys_selected_values["D"] = false
	keys_selected_values["D#"] = false
	keys_selected_values["Select ALL"] = false

##------------------------------------------------------------------------------

func init_settings() -> void:
	is_sound_fx_enabled = true
	audio_output = AudioServer.get_output_device()
	audio_input = AudioServer.get_input_device()

##------------------------------------------------------------------------------

func save_settings() -> void:
	fs.save_settings()

func save_project() -> void:
	var err = ProjectSettings.save_custom("user://config.godot")
	if err != OK: OS.alert("save error")
	OS.alert("Needs restart to save settings")

# GlobalVars.gd

extends Node

# Variables
var audio_analyzer: Node
var main_scene_workspace: Panel

##------------------------------------------------------------------------------

func _ready() -> void:
	set_process(false)

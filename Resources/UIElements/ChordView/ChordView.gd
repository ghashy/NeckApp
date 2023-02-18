# ChordView.gd

extends Control

# Signals
signal finish_view

# Onready variables
@onready var label: Label = $Label

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	set_process(false)

func success() -> void:
	label.modulate = Color.GREEN
	await get_tree().create_timer(1).timeout
	emit_signal("finish_view")
	label.modulate = Color.WHITE

func init_view(chord: String) -> void:
	label.text = chord

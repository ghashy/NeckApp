# ValuesLabel.gd

extends Control

# Onready variables
@onready var left: Label = $HBox/Left
@onready var left_shadow: Label = $Shadow/Left
@onready var colon: Label = $HBox/Colon
@onready var colon_shadow: Label = $Shadow/Colon
@onready var right: Label = $HBox/Right
@onready var right_shadow: Label = $Shadow/Right

func _ready() -> void:
	var tween: Tween = get_tree().create_tween()
	tween.tween_property(colon, "modulate", Color.TRANSPARENT, 1.0) \
		.set_ease(Tween.EASE_OUT) \
		.set_trans(Tween.TRANS_CUBIC)
	tween.tween_property(colon, "modulate", Color.WHITE, 1.0) \
		.set_ease(Tween.EASE_OUT) \
		.set_trans(Tween.TRANS_CUBIC)
	tween.set_loops()
	var tween_shadow: Tween = get_tree().create_tween()
	tween_shadow.tween_property(colon_shadow, "modulate", Color.TRANSPARENT, 1.0) \
		.set_ease(Tween.EASE_OUT) \
		.set_trans(Tween.TRANS_CUBIC)
	tween_shadow.tween_property(colon_shadow, "modulate", Color.WHITE, 1.0) \
		.set_ease(Tween.EASE_OUT) \
		.set_trans(Tween.TRANS_CUBIC)
	tween_shadow.set_loops()

func set_values(values: Dictionary) -> void:
	left.set_text(str(values["degree"]))
	left_shadow.set_text(str(values["degree"]))
	right.set_text(str(values["string"]))
	right_shadow.set_text(str(values["string"]))

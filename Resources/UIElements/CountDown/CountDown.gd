# CountDown.gd

extends Control

@onready var digit_array: Array[Label] = [get_node("Digit_3") as Label,
											get_node("Digit_2") as Label,
											get_node("Digit_1") as Label]

signal countdown_finished

func _ready() -> void:
	for label in digit_array:
		label.hide()
	var tween: Tween = get_tree().create_tween()
	digit_array[0].show()
	tween.tween_property(digit_array[0], "scale", Vector2.ZERO, 1.0)
	await tween.finished
	tween = get_tree().create_tween()
	digit_array[1].show()
	tween.tween_property(digit_array[1], "scale", Vector2.ZERO, 1.0)
	await tween.finished
	tween = get_tree().create_tween()
	digit_array[2].show()
	tween.tween_property(digit_array[2], "scale", Vector2.ZERO, 1.0)
	await tween.finished
	emit_signal("countdown_finished")

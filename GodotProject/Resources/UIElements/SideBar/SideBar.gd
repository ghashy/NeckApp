# SideBar.gd

class_name SideBar extends Panel

var x_min: float = DisplayServer.window_get_size().x - self.size.x
var x_max: float = DisplayServer.window_get_size().x
var sidebar_pos: Vector2:
	set(value):
		if (value.x < x_min or value.x > x_max): return
		sidebar_pos = position
		position = value

##------------------------------------------------------------------------------

func _ready() -> void:
	await get_parent().ready
	sidebar_pos = self.position

##------------------------------------------------------------------------------

func finalize_motion(tween: Tween, relative: Vector2, sb_swift: float) -> void:
	if tween and tween.is_valid():
		return
	tween = get_tree().create_tween()
	if (sign(relative.x) > 0):
		var tweener: Tweener = tween.tween_property(self, "sidebar_pos",
												Vector2(x_max, 0.0), sb_swift)
		tweener.set_trans(Tween.TRANS_CUBIC).set_ease(Tween.EASE_OUT)
	else:
		var tweener: Tweener = tween.tween_property(self, "sidebar_pos",
												Vector2(x_min, 0.0), sb_swift)
		tweener.set_trans(Tween.TRANS_CUBIC).set_ease(Tween.EASE_OUT)

##------------------------------------------------------------------------------

func update_constrains() -> void:
	x_min = DisplayServer.window_get_size().x - self.size.x
	x_max = DisplayServer.window_get_size().x
	sidebar_pos = position

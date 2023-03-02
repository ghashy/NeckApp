# Utils.gd

class_name Utils extends Node

func _ready() -> void:
	set_process(false)

## Transform selected keys to array, which can be read out by cpp.
static func get_keys_for_cpp() -> Array[int]:
	var from: Dictionary = GlobalSettings.keys_selected_values
	var result: Array[int] = []
	for key in from:
		if key == "C" and from[key] == true:
			result.push_back(0)
		if key == "C♯" and from[key] == true:
			result.push_back(1)
		if key == "D" and from[key] == true:
			result.push_back(2)
		if key == "D♯" and from[key] == true:
			result.push_back(3)
		if key == "E" and from[key] == true:
			result.push_back(4)
		if key == "F" and from[key] == true:
			result.push_back(5)
		if key == "F♯" and from[key] == true:
			result.push_back(6)
		if key == "G" and from[key] == true:
			result.push_back(7)
		if key == "G♯" and from[key] == true:
			result.push_back(8)
		if key == "A" and from[key] == true:
			result.push_back(9)
		if key == "B♭" and from[key] == true:
			result.push_back(10)
		if key == "B" and from[key] == true:
			result.push_back(11)  
	return result

static func get_alternation() -> int:
	match GlobalSettings.alternation_selected_value:
		0:
			return 1
		1:
			return randi_range(3, 5)
		2:
			return randi_range(5, 10)
		3:
			return randi_range(10, 15)
		4:
			return 100000 # I think it the same as 'NO ALTERNATION' :)
		_:
			return 1 # Can never happens.

# Amature tonalities: C, C♯, D, D♯, E, F, F♯, G, G♯, A, B♭, B
static func int_to_key_s(key: int) -> String:
	if GlobalSettings.is_modern:
		match key:
			0: return "c"
			1: return "c♯"
			2: return "d"
			3: return "d♯"
			4: return "e"
			5: return "f"
			6: return "f♯"
			7: return "g"
			8: return "g♯"
			9: return "a"
			10: return "b♭"
			11: return "b"
			_: return "unknown"
	else:
		match key:
			0: return "c"
			1: return "cis"
			2: return "d"
			3: return "dis"
			4: return "e"
			5: return "f"
			6: return "fis"
			7: return "g"
			8: return "gis"
			9: return "a"
			10: return "b"
			11: return "h"
			_: return "unknown"

# Generator.gd

class_name Generator extends RefCounted

var s: int
var d: int
var result: Dictionary
var pairs: Array[String] = []
var idx: int = 0
var last_s = 0
var last_d = 0

func _init() -> void:
	for i in range(0, 25):
		pairs.push_back("")

func get_values() -> Dictionary:

	# First step generation.
	s = get_s_value()
	d = get_d_value()

	# Fix duplicated pairs.
	fix()

	# Add to vector.
	pairs[idx] = str(s) + "-" + str(d)

	last_s = s
	last_d = d
	if idx < 24:
		idx += 1
	else:
		idx = 0

	result["string"] = s
	result["degree"] = d
	return result

func fix() -> void:
	var key: String = str(s) + "-" + str(d)
	while pairs.find(key) != -1 or s == last_s or d == last_d:
		s = get_s_value()
		d = get_d_value()
		key = str(s) + "-" + str(d)

func is_duplicated_two_times() -> bool:
	for i in pairs.size():
		if pairs[i].length() > 2:
			var t_d = pairs[i][0].to_int()
			var t_s = pairs[i][2].to_int()
			if t_d == d and t_s == s: return true
	return false

func get_d_value() -> int:
	var rand: RandomNumberGenerator = RandomNumberGenerator.new()
	rand.randomize()
	return rand.randi_range(1, 7)

func get_s_value() -> int:
	var rand: RandomNumberGenerator = RandomNumberGenerator.new()
	rand.randomize()
	return rand.randi_range(2, 6)

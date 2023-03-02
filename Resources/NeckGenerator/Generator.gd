# Generator.gd

class_name Generator extends RefCounted

var result: Dictionary

func get_values() -> Dictionary:
	var pairs: Array[String] = []

	for i in range(1, 25):
		pairs.push_back("0")
	
	var idx: int = 0
	var last_r = 0;

	# First step generation.
	var s: int = get_s_value();
	var d: int = get_d_value();

	# Fix duplicated pairs.
	fix(pairs, s, d, last_r, idx);

	# Add to vector.
	pairs[idx] = str(s) + "-" + str(d);

	last_r = d
	if idx < 24: idx += 1
	else: idx = 0;

	result["string"] = s
	result["degree"] = d
	return result;


func fix(pairs: Array[String], s: int, d: int, last: int, idx: int) -> void:
	var key: String = str(s) + "-" + str(d);
	while (pairs.find(key) != -1 or d == last or is_duplicated_two_times(pairs, s, idx)):
		s = get_s_value();
		d = get_d_value();
		key = str(s) + "-" + str(d)

func is_duplicated_two_times(p_str: Array[String], s: int, idx: int) -> bool:
	for i in range(1, 2):
		var temp: int = p_str[idx].to_int()
		if temp == s: return true
		idx -= i;
	return false;

func get_d_value() -> int:
	var rand: RandomNumberGenerator = RandomNumberGenerator.new()
	rand.randomize();
	return rand.randi_range(1, 7);

func get_s_value() -> int:
	var rand: RandomNumberGenerator = RandomNumberGenerator.new()
	rand.randomize();
	return rand.randi_range(2, 6);

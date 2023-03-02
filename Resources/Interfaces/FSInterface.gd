# ClientSaver.gd

class_name FSIntervace extends RefCounted

func _init():
	pass

func save_settings() -> void:
	var file := init_file("Settings.txt", FileAccess.WRITE)
	file.store_8(GlobalSettings.alternation_selected_value)
	file.store_8(GlobalSettings.is_modern)
	file.store_var(GlobalSettings.keys_selected_values, true)

func load_settings() -> void:
	var file := init_file("Settings.txt", FileAccess.READ)
	if file == null: return
	if file.get_length() == 0:
		return
	GlobalSettings.alternation_selected_value = file.get_8()
	GlobalSettings.is_modern = file.get_8()
	GlobalSettings.keys_selected_values = file.get_var(true)

func save_rewards() -> void:
	pass

func load_rewards() -> void:
	pass

func init_file(name: String, flag: int) -> FileAccess:
	var path := "user://"
	var file := FileAccess.open(path + name, flag)
	if file == null: return
	if FileAccess.get_open_error() != OK:
		OS.alert("Can not open Settings.txt file")
	return file


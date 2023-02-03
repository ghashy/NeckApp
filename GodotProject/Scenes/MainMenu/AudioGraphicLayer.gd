# AudioGraphicLayer.gd

extends Control

@onready var volume_meter: ProgressBar = $VolumeMeter
@onready var label: Label = $VolumeMeter/Label
@onready var samples_vol_arr: Array[float] = []

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	var bus_index: int = AudioServer.get_bus_index("InputBus")
	var volume: float = AudioServer.get_bus_peak_volume_left_db(bus_index, 0)

	samples_vol_arr.push_front(volume)

	if samples_vol_arr.size() > 20:
		samples_vol_arr.pop_back()
	
	var avg: float = get_average_sample_strength()
	label.text = "%s db" % round(avg)
	volume_meter.value = avg

##------------------------------------------------------------------------------

func get_average_sample_strength() -> float:
	var avg: float = 0.0
	for i in samples_vol_arr:
		avg += i
	return avg / samples_vol_arr.size()

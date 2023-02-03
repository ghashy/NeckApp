# AudioAnalyzeInterface.gd

extends Node

# Signals
signal analyze_ready

# Variables
var chord_info: ChordInfo = ChordInfo.new()
var input_gain_level: float
var threshold: float = -30.0
var frame_size: int = 1024
var capture_effect: AudioEffectCapture = AudioServer.get_bus_effect(
	AudioServer.get_bus_index("InputBus"), 0) as AudioEffectCapture
var sample_rate: int = int(AudioServer.get_mix_rate())

var chord: TargetChord

##------------------------------------------------------------------------------

# Onready variables

func _ready() -> void:
	set_process(false)
	GlobalVars.audio_analyzer = self
	connect_signals()

##------------------------------------------------------------------------------

func connect_signals() -> void:
	GlobalVars.main_scene_workspace.start_analyze.connect(start_analyze)
##------------------------------------------------------------------------------

func _process(_delta: float) -> void:
	input_gain_level = AudioServer.get_bus_peak_volume_left_db(
						AudioServer.get_bus_index("InputBus"), 0)
	
	var can_get_buffer: bool = capture_effect.can_get_buffer(frame_size * 50)
	if input_gain_level > threshold and can_get_buffer:
		var num_samples: int = capture_effect.get_frames_available()
		# If we remove calculation_interval arg from calculate_result() in cpp, there are happens a unknown maginc error, so leave it as is
		var result: bool = chord_info.calculate_result(capture_effect.get_buffer(num_samples / 2), num_samples / 2, frame_size, sample_rate, chord)
		if result:
			emit_signal("analyze_ready")
			set_process(false)

##------------------------------------------------------------------------------ 

## Method starts, triggered by signal [start_analyze], registered in the root.
## [chord] parameter - uses for compare target with audio information.
func start_analyze(target: TargetChord) -> void:
	chord = target
	set_process(true)

##------------------------------------------------------------------------------

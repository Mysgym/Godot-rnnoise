extends Node

#get capture effect
var capture = AudioServer.get_bus_effect(AudioServer.get_bus_index("Micin"),0) as AudioEffectCapture

#create denoiser object
@onready var denoiser : AudioDenoiser = AudioDenoiser.new()

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	while(capture.can_get_buffer(denoiser.get_frame_size())):
		#get capture frame
		var frame = capture.get_buffer(denoiser.get_frame_size())
		#convert to mono, the only supported format
		var mono = denoiser.stereo_to_mono(frame, 0)
		#denoise
		mono = denoiser.process_frame(mono)
		#convert back to stereo
		var stereo = denoiser.mono_to_stereo(mono,mono)
		#output
		$Output.get_stream_playback().push_buffer(stereo)

# Godot-rnnoise

This is a godot extension based on the [rnnoise project](https://gitlab.xiph.org/xiph/rnnoise) allowing for real-time processing of voice recordings, removing background noises.
<br>
## Building

This project is built using Scons, and requires an [rnnoise](https://gitlab.xiph.org/xiph/rnnoise) static library. A precompiled library for linux is provided in the lib/bin folder.

Although this project has only been tested on linux, it should work on windows and macos provided an rnnoise binary and minor adjustments to the SConstruct file.
Windows and macOS support is currently a work in progress, I encourage anyone attempting to compile for those OS to report any encountered issue and create pull requests for functional builds.

  1 - Clone this repo and the godot-cpp submodule  
  `git clone https://github.com/Mysgym/Godot-rnnoise && cd Godot-rnnoise`

  2 - Build using scons  
  `scons`

  3 - Run the demo project or add the extension to your own project by copying the content of the demo/addons folder to your project's addons folder.
<br>

## Usage

### Demo

The demo folder containes an example godot project using this extension to remove background noise from the microphone input.
The relevant code snippet is the following :

```gdscript
#get capture effect
var capture = AudioServer.get_bus_effect(AudioServer.get_bus_index("Micin"),0) as AudioEffectCapture

#create denoiser object
@onready var denoiser : AudioDenoiser = AudioDenoiser.new()

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
```  
### Methods detail
This extension adds a "Denoiser" object to godot, which itself implements the following methods :

| Method definition | Method description |
| ------------------|--------------------|
| process_frame(frame : PackedFloat32Array) -> PackedFloat32Array | Denoises a frame of audio data.<br>Rnnoise limitations impose : mono signal, 48kHz sampling rate, specific size (see get_frame_size()) |
| get_frame_size() -> int | Returns the size of the frame expected by process_frame(). Constant |
| stereo_to_mono(frame : PackedVector2Array, mode : int) -> PackedFloat32Array | Transforms stereo signal to mono with three possible modes : <br> 0. returns left signal <br> 1. returns right signal <br> 2. averages left and right signals|
| mono_to_stereo(left : PackedFloat32Array, right: PackedFloat32Array) -> PackedVector2Array | Combines two mono frames into a single stereo frame|  
<br>  

## Contributing

This project is being actively maintained, any reported issue and contributions are greatly appreciated.

Windows and macOS users are encouraged to attempt compilation and share their work as I personally lack easy access to those OS.

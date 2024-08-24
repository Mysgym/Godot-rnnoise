# Godot-rnnoise

This is a godot extension based on the [rnnoise project](https://gitlab.xiph.org/xiph/rnnoise) allowing for real-time processing of voice recordings, removing background noises.
<br>
## Building

This project is built using Scons, and requires an [rnnoise](https://gitlab.xiph.org/xiph/rnnoise) static library. A precompiled library for linux is provided in the lib/bin folder.

  1 - Clone this repo and the godot-cpp submodule  
  ```
  git clone --recurse-submodules https://github.com/Mysgym/Godot-rnnoise && cd Godot-rnnoise
  ```

  2 - Build using scons  
  ```
  scons
  ```

  3 - Add the extension to your own project by copying the contents of the addons folder to your project's addons folder.  

Although this project has only been tested on linux, it should work on windows and macos provided an rnnoise binary and minor adjustments to the SConstruct file.  
Windows and macOS support is currently a work in progress, I encourage anyone attempting to compile for those OS to report any encountered issue and create pull requests for functional builds.

## Usage

### Demo

### Methods detail
This extension adds an "AudioDenoiser" object to godot, which itself implements the following methods :

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

## License

this project is MIT licensed, it uses [rnnoise](https://gitlab.xiph.org/xiph/rnnoise) which is under the BSD 3-Clause license.

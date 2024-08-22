#include "denoiser.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

AudioDenoiser::AudioDenoiser(){
	denoiseState = rnnoise_create(NULL);
	ERR_FAIL_COND(denoiseState == NULL);
}

AudioDenoiser::~AudioDenoiser(){
	rnnoise_destroy(denoiseState);

}

void AudioDenoiser::map_to_16bit(float* input, int size){
	
	for(int i = 0; i < size; i++){
		input[i] *= SIGNED_16_BIT_MAX;
	}
	
}

void AudioDenoiser::map_to_1(float* input, int size){

	for(int i = 0; i < size; i++){
		input[i] /= SIGNED_16_BIT_MAX;
	}
}

PackedFloat32Array AudioDenoiser::process_frame(PackedFloat32Array frame){
	if(frame.size() != get_frame_size()){
		UtilityFunctions::printerr("GODOT RNNOISE ERROR : Frame size is : ", frame.size(), ", expected : ", get_frame_size());
		return frame;
	}

	map_to_16bit((float*) frame.ptrw(), frame.size());

	rnnoise_process_frame(denoiseState, (float*) frame.ptrw(), (float*) frame.ptr());
	
	map_to_1((float*) frame.ptrw(), frame.size());

	return frame;

}	

int AudioDenoiser::get_frame_size(){
	return rnnoise_get_frame_size();
}

PackedFloat32Array AudioDenoiser::stereo_to_mono(PackedVector2Array stereo, int mode){
	PackedFloat32Array mono;
	mono.resize(stereo.size());

	float* monoData = (float*) mono.ptrw();
	float* stereoData = (float*) stereo.ptr();

	for(int i = 0; i < stereo.size(); i++){
		if(mode == 2) monoData[i] = ((stereoData[2*i]+stereoData[2*i+1])/2);
		else monoData[i] = stereoData[2*i + mode];
	}
	return mono;

}
			
PackedVector2Array AudioDenoiser::mono_to_stereo(PackedFloat32Array left, PackedFloat32Array right){
	
	PackedVector2Array stereo;
	stereo.resize(left.size());
	
	if(left.size() != right.size()){
		UtilityFunctions::printerr("GODOT RNNOISE ERROR : Cannot convert from mono to stereo, mismatched size between left and right channel");
		return stereo;
	}

	
	float* leftData = (float*) left.ptr();
	float* rightData = (float*) right.ptr();
	float* stereoData = (float*) stereo.ptrw();

	for(int i = 0; i < stereo.size(); i++){
		stereoData[2*i] = leftData[i];
		stereoData[2*i+1] = rightData[i];
	}

	return stereo;

}

void AudioDenoiser::_bind_methods(){
	
	ClassDB::bind_method(D_METHOD("process_frame"), &AudioDenoiser::process_frame);
	ClassDB::bind_method(D_METHOD("get_frame_size"), &AudioDenoiser::get_frame_size);
	ClassDB::bind_method(D_METHOD("stereo_to_mono"), &AudioDenoiser::stereo_to_mono);
	ClassDB::bind_method(D_METHOD("mono_to_stereo"), &AudioDenoiser::mono_to_stereo);
}

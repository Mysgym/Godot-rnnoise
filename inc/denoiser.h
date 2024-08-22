#ifndef GODOT_DENOISER_H
#define GODOT_DENOISER_H

#include <godot_cpp/classes/node.hpp>
#include "rnnoise.h"

#define SIGNED_16_BIT_MAX 32768

namespace godot{
	
	class AudioDenoiser : public Object {
		GDCLASS(AudioDenoiser, Object);

		protected:
			static void _bind_methods();
			DenoiseState* denoiseState;

			//utility functions to convert from godot's (-1 to +1) encoding to rnnoise's (16 bit) 
			void map_to_16bit(float* input, int size);
			void map_to_1(float* input, int size);

		public:
			AudioDenoiser();
			~AudioDenoiser();
			
			//utility functions to switch between mono and stereo
			//modes : 0 only left, 1 only right, 2 average
			PackedFloat32Array stereo_to_mono(PackedVector2Array stereo, int mode);
			PackedVector2Array mono_to_stereo(PackedFloat32Array left, PackedFloat32Array right);	

			//Sampling rate should be 48000
			PackedFloat32Array process_frame(PackedFloat32Array frame);		
			int get_frame_size();

	};

}


#endif

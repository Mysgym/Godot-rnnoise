#include "register_types.h"

#include "denoiser.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_rnnoise_module(ModuleInitializationLevel p_level){
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<AudioDenoiser>();	
}

void uninitialize_rnnoise_module(ModuleInitializationLevel p_level){
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	return;
}

extern "C" {

	GDExtensionBool GDE_EXPORT godot_rnnoise_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
		   	const GDExtensionClassLibraryPtr p_library,
			GDExtensionInitialization *r_initialization)
	
	{
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		init_obj.register_initializer(initialize_rnnoise_module);
		init_obj.register_terminator(uninitialize_rnnoise_module);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);	

		return init_obj.init();
	
	}


}

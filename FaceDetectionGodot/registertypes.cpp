// #include<godot_cpp/core/defs.hpp>
// #include<godot_cpp/core/class_db.hpp>
// #include<godot_cpp/godot.hpp>
// #include "enginebase.h"
// #include "facedetect.h"
// #include"registertypes.h"
// #include<gdextension_interface.h>


// void initialize_face_detect(godot::ModuleInitializationLevel p_level){
//     if(p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE){
//         return;
//     }
//     godot::ClassDB::register_class<FaceDetect>();

// }

// void uninitialize_face_detect(godot::ModuleInitializationLevel p_level){
//     if(p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE){
//         return;
//     }
// }

// extern "C"{
// GDExtensionBool GDE_EXPORT face_detect_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization){
//     godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

//     init_obj.register_initializer(initialize_face_detect);
//     init_obj.register_terminator(uninitialize_face_detect);
//     init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

//     return init_obj.init();
// }

// }

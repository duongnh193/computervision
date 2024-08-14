#include "register.h"
#include "testgde.h"
#include "testopencv.h"
#include "testcam.h"

void initialize_test(godot::ModuleInitializationLevel p_level){
    if(p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE){
        return;
    }
    godot::ClassDB::register_class<TestGDE>();
    godot::ClassDB::register_class<TestOpenCV>();
    godot::ClassDB::register_class<testcam>();
}

void uninitialize_test(godot::ModuleInitializationLevel p_level){
    if(p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE){
        return;
    }
}

extern "C"{
GDExtensionBool GDE_EXPORT test_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization){
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_test);
    init_obj.register_terminator(uninitialize_test);
    init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
    }
}

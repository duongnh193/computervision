#include "testgde.h"

void TestGDE::_bind_methods(){
    godot::ClassDB::bind_method(godot::D_METHOD("get_speed"), &TestGDE::get_speed);
    godot::ClassDB::bind_method(godot::D_METHOD("set_speed", "p_speed"), &TestGDE::set_speed);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "speed", godot::PROPERTY_HINT_RANGE, "0,20,0.01"), "set_speed", "get_speed");
    ADD_SIGNAL(godot::MethodInfo("position_changed", godot::PropertyInfo(godot::Variant::OBJECT, "node"), godot::PropertyInfo(godot::Variant::VECTOR2, "new_pos")));
}



TestGDE::TestGDE() {
    time_passed = 0.0;
    amplitude = 10.0;
    speed = 1.0;
    time_emit = 0.0;
}

TestGDE::~TestGDE(){}

void TestGDE::_process(double delta){
    time_passed += speed * delta;

    godot::Vector2 new_position = godot::Vector2(
        amplitude + (amplitude * sin(time_passed * 2.0)),
        amplitude + (amplitude * cos(time_passed * 1.5))
        );

    set_position(new_position);

    time_emit += delta;
    if (time_emit > 1.0){
        emit_signal("position_changed", this, new_position);
        time_emit = 0.0;
    }
}

void TestGDE::set_speed(const double p_speed) {
    speed = p_speed;
}

double TestGDE::get_speed() const {
    return speed;
}




#include "test.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <opencv2/core.hpp>

test::test() {
    time_passed = 0.0;
}

test::~test(){}

void test::_process(double delta){
    time_passed += delta;

    godot::Vector2 new_position = godot::Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

    set_position(new_position);
}

void test::_bind_methods(){}

#ifndef TEST_H
#define TEST_H
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

class test : public godot::Sprite2D
{
    GDCLASS(test, godot::Sprite2D)
public:
    test();
    ~test();
    void _process(double delta) override;
private:
    double time_passed;
protected:
    static void _bind_methods();
};

#endif // TEST_H

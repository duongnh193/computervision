#ifndef TESTGDE_H
#define TESTGDE_H
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/sprite2d.hpp>


class TestGDE : public godot::Sprite2D
{
    GDCLASS(TestGDE, godot::Sprite2D)
public:
    TestGDE();
    ~TestGDE();
    void _process(double delta) override;
    // void set_amplitude(const double p_amplitude);
    // double get_amplitude() const;
    void set_speed(const double p_speed);
    double get_speed() const;
private:
    double time_passed;
    double amplitude;
    double speed;
    double time_emit;
protected:
    static void _bind_methods();
};

#endif // TESTGDE_H

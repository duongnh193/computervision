#ifndef TESTOPENCV_H
#define TESTOPENCV_H

#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/texture.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp//classes/texture_rect.hpp>
#include <godot_cpp//classes/os.hpp>

class TestOpenCV : public godot::Node2D
{
    GDCLASS(TestOpenCV, godot::Node2D)
public:
    TestOpenCV();
    ~TestOpenCV();
    void _process(double delta) override;
    double lastTime=0;
    bool isChange = 0;
    godot::Ref<godot::ImageTexture> texture;
    godot::Ref<godot::ImageTexture> getTexture() const;
    void setTexture(const godot::Ref<godot::ImageTexture> &newTexture);
    godot::Ref<godot::Image> img;

    double speed = 0.0;
    void set_speed(const double p_speed);
    double get_speed() const;
protected:
    static void _bind_methods();

    // Node interface
    // public:
    // void _ready() override;

    // Node interface
public:
    void _ready() override;
    godot::Ref<godot::Image> getImg() const;
    void setImg(const godot::Ref<godot::Image> &newImg);
};





#endif // TESTOPENCV_H

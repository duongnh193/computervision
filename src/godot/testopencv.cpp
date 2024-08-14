#include "testopencv.h"
#include "godot_cpp/variant/utility_functions.hpp"

void TestOpenCV::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("getTexture"), &TestOpenCV::getTexture);
    godot::ClassDB::bind_method(godot::D_METHOD("setTexture", "newTexture"), &TestOpenCV::setTexture);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "texturengu", godot::PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "setTexture", "getTexture");


    godot::ClassDB::bind_method(godot::D_METHOD("getImg"), &TestOpenCV::getImg);
    godot::ClassDB::bind_method(godot::D_METHOD("setImg", "new_image"), &TestOpenCV::setImg);
    // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "image", godot::PROPERTY_HINT_RESOURCE_TYPE, "Image"), "setImg", "getImg");



    godot::ClassDB::bind_method(godot::D_METHOD("get_speed"), &TestOpenCV::get_speed);
    godot::ClassDB::bind_method(godot::D_METHOD("set_speed", "p_speed"), &TestOpenCV::set_speed);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "speed", godot::PROPERTY_HINT_RANGE, "0,20,0.01"), "set_speed", "get_speed");
}

void TestOpenCV::_ready()
{
    godot::UtilityFunctions::print("enter ready");
    cv::Mat image = cv::imread("/home/duongnh/Downloads/img test/face2.jpg");
    // img = godot::Image::create(image.cols, image.rows, false, godot::Image::FORMAT_RGB8);
    cv::imwrite("/home/duongnh/Downloads/img test/ryu_cv.jpg", image);
    // godot::UtilityFunctions::print("img size: ", img.get_format(), " ", img.get_height(), " ", img.get_width());
    godot::PackedByteArray data;
    data.resize(image.cols *image.rows * 3);
    memcpy(data.ptrw(), image.data, image.total() * image.elemSize());
    // godot::UtilityFunctions::print("opencv image data", (int)image.at<cv::Vec3b>(0,0)[0]);
    // godot::UtilityFunctions::print("opencv image data", (int)image.at<cv::Vec3b>(0,0)[1]);
    // godot::UtilityFunctions::print("opencv image data", (int)image.at<cv::Vec3b>(0,0)[2]);
    // godot::UtilityFunctions::print("pack data", data[0]);
    // godot::UtilityFunctions::print("pack data", data[1]);
    // godot::UtilityFunctions::print("pack data", data[2]);
    img = img->create_from_data(image.cols, image.rows, false, godot::Image::FORMAT_RGB8, data);

    // img->save_jpg("/home/duongnh/Downloads/img test/ryu.jpg",1);

    texture.instantiate();
    texture = texture->create_from_image(img);
    // godot::UtilityFunctions::print("data size: " , data.size());
}

TestOpenCV::TestOpenCV() {
    if(godot::Engine::get_singleton() -> is_editor_hint()){
        set_process_mode(godot::Node::ProcessMode::PROCESS_MODE_DISABLED);
    }
}

void TestOpenCV::_process(double delta){
    auto currentMil  = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    if(currentMil - lastTime > 5000){
        godot::UtilityFunctions::print("change image");
        lastTime = currentMil;
        godot::Ref<godot::Image> image ;
        if(isChange)
            image = godot::Image::load_from_file("/home/duongnh/Downloads/img test/trump1.jpeg");
        else
            image = godot::Image::load_from_file("/home/duongnh/Downloads/img test/trump2.jpeg");

        texture = texture->create_from_image(image);
        isChange = !isChange;
    }
}

godot::Ref<godot::ImageTexture> TestOpenCV::getTexture() const
{
    return texture;
}



void TestOpenCV::setTexture(const godot::Ref<godot::ImageTexture> &newTexture)
{
    texture = newTexture;
}

void TestOpenCV::set_speed(const double p_speed) {
    speed = p_speed;
}

double TestOpenCV::get_speed() const {
    return speed;
}

godot::Ref<godot::Image> TestOpenCV::getImg() const
{
    return img;
}

void TestOpenCV::setImg(const godot::Ref<godot::Image> &newImg)
{
    img = newImg;
}

TestOpenCV::~TestOpenCV() {}

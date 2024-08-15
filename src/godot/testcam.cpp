#include "testcam.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <thread>
testcam::testcam() {
    if(godot::Engine::get_singleton() -> is_editor_hint()){
        set_process_mode(godot::Node::ProcessMode::PROCESS_MODE_DISABLED);
    }
}

testcam::~testcam(){
    stop();
}

void testcam::_ready()
{
}

double testcam::euclidean_distance(const cv::Point& p1, const cv::Point& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

bool testcam::is_mouth_open(const std::vector<cv::Point>& mouthLandmarks) {

    // if(mouthLandmarks.size()<16) return false;
    // godot::UtilityFunctions::print("size: " , mouthLandmarks.size());
    cv::Point p1 = mouthLandmarks[5];
    // godot::UtilityFunctions::print("p1: " , p1.x, p1.y);
    cv::Point p2 = mouthLandmarks[15];
    // godot::UtilityFunctions::print("p2: " , p2.x, p2.y);

    double distance = euclidean_distance(p1, p2);
    double threshold = 28;

    return distance > threshold;
}


void testcam::startThread()
{
    std::thread th1(&testcam::readCam, this);
    godot::UtilityFunctions::print("Thread before start");
    th1.detach();
    godot::UtilityFunctions::print("Thread after start");
}


void testcam::_process(double delta)
{
    timepass+=delta;
    if(timepass >= 5){
        emit_signal("ryu_timepass", timepass);
        timepass=0;
    }
}

void testcam::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("start"), &testcam::start);
    godot::ClassDB::bind_method(godot::D_METHOD("stop"), &testcam::stop);
    godot::ClassDB::bind_method(godot::D_METHOD("get_texture"), &testcam::getTexture);
    godot::ClassDB::bind_method(godot::D_METHOD("startThread"), &testcam::startThread);
    ADD_SIGNAL(godot::MethodInfo("is_mouth_open_left", godot::PropertyInfo(godot::Variant::BOOL, "isOpen")));
    ADD_SIGNAL(godot::MethodInfo("is_mouth_open_right", godot::PropertyInfo(godot::Variant::BOOL, "isOpen")));

    //ryu
    ADD_SIGNAL(godot::MethodInfo("ryu_timepass",godot::PropertyInfo(godot::Variant::FLOAT, "timepass")));
}


godot::Ref<godot::ImageTexture> testcam::getTexture()
{
    return texture;
}

void testcam::readCam()
{
    // godot::UtilityFunctions::print("in getTexture");
    my::FaceLandmark faceLandmark("/home/duongnh/Projects/Godot/Test GDE/src/models");
    auto current = CURRENTMIL;
    lastDelta = current;
    int deviceID = 0;
    int appID = cv::CAP_ANY;
    cap.open(deviceID,appID);
    while(cap.isOpened()) {
        cap >> frame;
        faceLandmark.loadImageToInput(frame);
        faceLandmark.runInference();
        // frame = faceLandmark.cropFrame(faceLandmark.getFaceRoi());
        auto mouths = faceLandmark.getMouthLandmarks();
        auto xCenter = faceLandmark.getcenterX(frame);
        if(mouths.at(5).x < xCenter) {
            for(auto mouth: mouths) {
                bool mouth_open = is_mouth_open(mouths);
                isOpenLeft = mouth_open;
                if(mouth_open){
                    cv::circle(frame, mouth, 2, cv::Scalar(255, 255, 0), -1);
                    if(!lastMouthLeftOpen){
                        lastMouthLeftOpen = true;
                        // godot::UtilityFunctions::print("before emit left mouth signal");
                        call_deferred("emit_signal","is_mouth_open_left", isOpenLeft);
                    }
                }else if(lastMouthLeftOpen){
                    lastMouthLeftOpen = false;
                } else {
                    cv::circle(frame, mouth, 2, cv::Scalar(0, 255, 0), -1);
                }
            }
        } else {
            faceLandmark.loadImageToInput(frame);
            faceLandmark.runInference();
            auto rightMouths = faceLandmark.getMouthLandmarks();
            for(auto rightmouth: rightMouths) {
                bool mouthRightOpen = is_mouth_open(rightMouths);
                isOpenRight = mouthRightOpen;
                if (mouthRightOpen){
                    cv::circle(frame, rightmouth, 2, cv::Scalar(255, 0, 0), -1);
                    if(!lastMouthRightOpen){
                        lastMouthRightOpen = true;
                        call_deferred("emit_signal", "is_mouth_open_right", isOpenLeft);
                    }
                }else if(lastMouthRightOpen){
                    lastMouthRightOpen = false;
                } else {
                    cv::circle(frame, rightmouth, 2, cv::Scalar(0, 196, 255), -1);
                }
            }
        }

        godot::PackedByteArray data;
        data.resize(frame.total() * frame.elemSize());
        memcpy(data.ptrw(), frame.data, data.size());
        image = image->create_from_data(frame.cols, frame.rows, false, godot::Image::FORMAT_RGB8, data);
        image->flip_x();
        texture.instantiate();
        texture = texture->create_from_image(image);
    }
}


void testcam::start()
{
    if(cap.isOpened()) {
        cap.open(0);
    }
}

void testcam::stop()
{
    if(cap.isOpened()) {
        cap.release();
    }
}


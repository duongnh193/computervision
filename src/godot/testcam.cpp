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
    ADD_SIGNAL(godot::MethodInfo("is_mouth_open_left"));
    ADD_SIGNAL(godot::MethodInfo("is_mouth_open_right"));

    //ryu
    // ADD_SIGNAL(godot::MethodInfo("ryu_timepass",godot::PropertyInfo(godot::Variant::FLOAT, "timepass")));
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
        std::vector<my::Detection> faces = faceLandmark.inference();
        godot::UtilityFunctions::print("face size: ", faces.size());
        if(!faces.empty()){
            for(my::Detection &face : faces){
                face.roi = cv::Rect2f(face.roi.x*frame.cols, face.roi.y*frame.rows, face.roi.width*frame.cols, face.roi.height*frame.rows);
                cv::rectangle(frame, face.roi, cv::Scalar(0,0,255),2);
                godot::UtilityFunctions::print("ROI width: ", face.roi.width, " || ROI height: ", face.roi.height);
                godot::UtilityFunctions::print("Frame width: ", frame.rows, " || Frame height: ", frame.cols);
                if(0 < face.roi.width < frame.rows && 0 < face.roi.height < frame.cols)
                {
                    godot::UtilityFunctions::print(__LINE__, " bug");
                    cv::Mat faceMat = frame(face.roi);
                    faceLandmark.loadImageToInput(faceMat);
                    faceLandmark.runInference();
                    auto mouths = faceLandmark.getMouthLandmarks();
                    bool mouth_open = is_mouth_open(mouths);
                    auto xCenter = frame.cols/2;
                    // godot::UtilityFunctions::print(__LINE__ , " ", __PRETTY_FUNCTION__);
                    // frame = faceLandmark.cropFrame(faceLandmark.getFaceRoi());
                    // for(auto& mouth:mouths){
                    //     cv::circle(frame, mouth, -1, cv::Scalar(255, 255, 0), -1);
                    // }
                    // godot::UtilityFunctions::print(__LINE__ , " ", __PRETTY_FUNCTION__);
                    godot::UtilityFunctions::print("Mouth size: ", mouths.size());
                    if(mouths.size() >= 6)
                    {
                        if(mouths.at(5).x + face.roi.x  < xCenter) {
                            if(!lastMouthLeftOpen && mouth_open){
                                call_deferred("emit_signal","is_mouth_open_left");
                            }
                            lastMouthLeftOpen = mouth_open;
                        } else{
                            if(!lastMouthRightOpen && mouth_open){
                                call_deferred("emit_signal","is_mouth_open_right");
                            }
                            lastMouthRightOpen = mouth_open;
                        }
                    } else {
                        godot::UtilityFunctions::print("No face detected!!");
                        continue;
                    }
                } else {
                    godot::UtilityFunctions::print("Invalid ROI!! Skip frame");
                    continue;
                }
            }
        } else {
            godot::UtilityFunctions::print("Error!! Face is null.");
            continue;
        }
        godot::UtilityFunctions::print(__LINE__, " " ,"face size: ", faces.size());
        godot::PackedByteArray data;
        godot::UtilityFunctions::print(__LINE__, " bug");
        data.resize(frame.total() * frame.elemSize());
        godot::UtilityFunctions::print(__LINE__, " bug");
        memcpy(data.ptrw(), frame.data, data.size());
        godot::UtilityFunctions::print(__LINE__, " bug");
        image = image->create_from_data(frame.cols, frame.rows, false, godot::Image::FORMAT_RGB8, data);
        godot::UtilityFunctions::print(__LINE__, " bug");
        image->flip_x();
        godot::UtilityFunctions::print(__LINE__, " bug");
        texture.instantiate();
        godot::UtilityFunctions::print(__LINE__, " bug");
        texture = texture->create_from_image(image);
        godot::UtilityFunctions::print(__LINE__, " bug");
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


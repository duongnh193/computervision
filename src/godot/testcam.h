#ifndef TESTCAM_H
#define TESTCAM_H
#include "testopencv.h"
#include "facelandmark.h"
#include <thread>

#define CURRENTMIL std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()
class testcam : public godot::Node2D
{
    GDCLASS(testcam, godot::Node2D)
public:
    testcam();
    ~testcam();
    void _ready() override ;
    void start();
    void stop();
    godot::Ref<godot::ImageTexture> getTexture() ;
    void readCam();
    double lastDelta=0.0;
    double isChange=0;
    std::vector<std::thread> threads;
    void startThread();
    float timepass=0;
protected:
    static void _bind_methods();
private:;
    cv::Mat frame;
    cv::VideoCapture cap;
    godot::Ref<godot::Image> image;
    godot::Ref<godot::ImageTexture> texture;
    double euclidean_distance(const cv::Point& p1, const cv::Point& p2);
    bool is_mouth_open(const std::vector<cv::Point>& mouthLandmarks);
    bool isOpenLeft = false;
    bool lastMouthLeftOpen = false;
    bool isOpenRight = false;
    bool lastMouthRightOpen = false;





    // Node interface
public:
    void _process(double delta) override;



};

#endif // TESTCAM_H

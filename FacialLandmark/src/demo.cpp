#include "irislandmark.h"
#include "facelandmark.h"
#include <iostream>
#include <opencv2/highgui.hpp>

#define SHOW_FPS    (1)

#if SHOW_FPS
#include <chrono>
#endif

double euclidean_distance(const cv::Point& p1, const cv::Point& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

bool is_mouth_open(const std::vector<cv::Point>& mouthLandmarks) {

    cv::Point p1 = mouthLandmarks[5];
    cv::Point p2 = mouthLandmarks[26];

    double distance = euclidean_distance(p1, p2);
    double threshold = 0.3;

    return distance > threshold;
}

int main(int argc, char* argv[]) {

    my::IrisLandmark irisLandmarker("/home/duongnh/Projects/Qt/FacialLandmark/models/");
    cv::VideoCapture cap(0);

    bool success = cap.isOpened();
    if (success == false)
    {
        std::cerr << "Cannot open the camera." << std::endl;
        return 1;
    }

#if SHOW_FPS
    float sum = 0;
    int count = 0;
#endif

    while (success)
    {
        cv::Mat rframe, frame;
        success = cap.read(rframe); // read a new frame from video

        if (success == false)
            break;

        cv::flip(rframe, rframe, 1);

#if SHOW_FPS
        auto start = std::chrono::high_resolution_clock::now();
#endif

        irisLandmarker.loadImageToInput(rframe);
        irisLandmarker.runInference();

        for (auto landmark: irisLandmarker.getMouthLandmarks()) {
            cv::circle(rframe, landmark, 2, cv::Scalar(0, 255, 0), -1);
            std::vector<cv::Point> mouthLandmarks = irisLandmarker.getMouthLandmarks();
            bool mouth_open = is_mouth_open(irisLandmarker.getMouthLandmarks());
            if  (mouth_open){
                cv::putText(rframe, "Open", cv::Point(270, 70), cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0, 196, 255), 2);
            } else {
                cv::putText(rframe, "Close", cv::Point(270, 70), cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0, 196, 255), 2);
            }
        }


#if SHOW_FPS
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        float inferenceTime = duration.count() / 1e3;
        sum += inferenceTime;
        count += 1;
        int fps = (int) 1e3/ inferenceTime;
        std::string show_fps = "FPS: " + std::to_string(fps);

        cv::putText(rframe, show_fps, cv::Point(20, 70), cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0, 196, 255), 2);
#endif

        cv::imshow("Face detector", rframe);

        if (cv::waitKey(10) == 27)
            break;
    }

#if SHOW_FPS
    std::cout << "Average inference time: " << sum / count << "ms " << std::endl;
#endif

    cap.release();
    cv::destroyAllWindows();
    return 0;
}

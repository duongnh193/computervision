// #include "irislandmark.h"
// #include <iostream>

// void my::IrisLandmark::_bind_methods(){}




// double euclidean_distance(const cv::Point& p1, const cv::Point& p2) {
//     return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
// }

// bool is_mouth_open(const std::vector<cv::Point>& mouthLandmarks) {

//     cv::Point p1 = mouthLandmarks[5];
//     cv::Point p2 = mouthLandmarks[15];

//     double distance = euclidean_distance(p1, p2);
//     double threshold = 28;

//     return distance > threshold;
// }

// void my::IrisLandmark::_process(double delta){
//     my::IrisLandmark irisLandmarker("/home/duongnh/Projects/Qt/FacialLandmark/models/");
//     cv::VideoCapture cap(0);

//     bool success = cap.isOpened();
//     if (success == false)
//     {
//         std::cerr << "Cannot open the camera." << std::endl;
//     }

//     while (success)
//     {
//         cv::Mat rframe, frame;
//         success = cap.read(rframe); // read a new frame from video

//         if (success == false)
//             break;

//         cv::flip(rframe, rframe, 1);
//         irisLandmarker.loadImageToInput(rframe);
//         irisLandmarker.runInference();

//         for (auto landmark: irisLandmarker.getMouthLandmarks()) {
//             cv::circle(rframe, landmark, 2, cv::Scalar(0, 255, 0), -1);
//             std::vector<cv::Point> mouthLandmarks = irisLandmarker.getMouthLandmarks();
//             bool mouth_open = is_mouth_open(irisLandmarker.getMouthLandmarks());
//             if  (mouth_open){
//                 cv::putText(rframe, "Open", cv::Point(270, 70), cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0, 196, 255), 2);
//             } else {
//                 cv::putText(rframe, "Close", cv::Point(270, 70), cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0, 196, 255), 2);
//             }
//         }

//         cap.release();
//         cv::destroyAllWindows();
//     }
// }

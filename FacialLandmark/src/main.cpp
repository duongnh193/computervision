// #include <QCoreApplication>
// #include <opencv2/opencv.hpp>
// #include <dlib/opencv.h>
// #include <dlib/image_processing.h>
// #include <dlib/image_processing/frontal_face_detector.h>
// #include <dlib/cuda/cuda_dlib.h>
// #include <iostream>


// // double euclidean_distance(dlib::point p1, dlib::point p2) {
// //     return sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));
// // }

// // // check mouth
// // bool is_mouth_open(dlib::full_object_detection shape) {
// //     double mouth_height = euclidean_distance(shape.part(62), shape.part(66));
// //     double mouth_width = euclidean_distance(shape.part(60), shape.part(64));
// //     return (mouth_height / mouth_width) > 0.25; // Ngưỡng xác định mở miệng
// // }

// // int main(int argc, char *argv[]) {
// //     QCoreApplication a(argc, argv);

// //     // if (!dlib::cuda::get_num_devices()) {
// //     //     std::cerr << "No CUDA devices found" << std::endl;
// //     //     return -1;
// //     // }
// //     std::cout << "Num of device using CUDA: " << dlib::cuda::get_num_devices() << std::endl;

// //     // std::cout << "CUDA is available and will be used by Dlib" << std::endl;
// //     // load Dlib
// //     dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
// //     dlib::shape_predictor predictor;
// //     dlib::deserialize("/home/duongnh/Downloads/shape_predictor_68_face_landmarks.dat") >> predictor;

// //     cv::Mat frame;
// //     cv::VideoCapture cap;
// //     int deviceID = 0; // 0 = open default camera
// //     int apiID = cv::CAP_ANY; // 0 = autodetect default API
// //     // open selected camera using selected API
// //     cap.open(deviceID, apiID);
// //     // check if we succeeded
// //     if (!cap.isOpened()) {
// //         std::cerr << "ERROR! Unable to open camera\n";
// //         return -1;
// //     }

// //     // int frameskip = 8;
// //     // int framecount = 0;

// //     std::cout << "Start grabbing" << std::endl
// //               << "Press any key to terminate" << std::endl;

// //     while (true) {
// //         cap.read(frame);
// //         if (frame.empty())
// //             break;

// //         // framecount++;
// //         // if (framecount % frameskip != 0) {
// //         //     imshow("Landmarks", frame);
// //         //     if (cv::waitKey(1) == 27)
// //         //         break;
// //         //     continue;
// //         // }
// //         // Covert to dlib::cv_image
// //         dlib::cv_image<dlib::bgr_pixel> cimg(frame);
// //         std::vector<dlib::rectangle> faces = detector(cimg);

// //         // draw
// //         for (auto& face : faces) {
// //             dlib::full_object_detection shape = predictor(cimg, face);

// //             bool mouth_open = is_mouth_open(shape);
// //             if (mouth_open) {
// //                 cv::putText(frame, "Open", cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
// //             } else {
// //                 cv::putText(frame, "Close", cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
// //             }

// //             for (int i = 48; i <= 68; ++i) {
// //                 cv::circle(frame, cv::Point(shape.part(i).x(), shape.part(i).y()), 1, cv::Scalar(0, 0, 255), 2);
// //             }

// //         }


// //         imshow("Landmarks", frame);
// //         if (cv::waitKey(1) == 27)
// //             break;
// //     }

// //     cap.release();
// //     cv::destroyAllWindows();

// //     return a.exec();
// // }

// std::vector<cv::Point> getMouthLandmarks(const std::vector<int>& lipsOuter, const std::vector<int>& lipsInner, const std::vector<cv::Point>& allLandmarks) {
//     std::vector<cv::Point> mouthLandmarks;

//     // Lấy tọa độ các điểm landmark từ lipsOuter
//     for (int idx : lipsOuter) {
//         mouthLandmarks.push_back(allLandmarks[idx]);
//     }

//     // Lấy tọa độ các điểm landmark từ lipsInner
//     for (int idx : lipsInner) {
//         mouthLandmarks.push_back(allLandmarks[idx]);
//     }

//     return mouthLandmarks;
// }

// int main() {
//     // Giả sử bạn đã có một vector chứa tất cả các tọa độ landmark của khuôn mặt
//     std::vector<cv::Point> allFaceLandmarks = {};

//     // Các chỉ số landmark của miệng
//     std::vector<int> lipsOuter = {
//         61, 185, 40, 39, 37, 0, 267, 269, 270, 409, 291,
//         375, 321, 405, 314, 17, 84, 181, 91, 146, 61
//     };

//     std::vector<int> lipsInner = {
//         78, 191, 80, 81, 82, 13, 312, 311, 310, 415, 308,
//         324, 318, 402, 317, 14, 87, 178, 88, 95, 78
//     };

//     // Lấy tọa độ các điểm landmark của miệng
//     std::vector<cv::Point> mouthLandmarks = getMouthLandmarks(lipsOuter, lipsInner, allFaceLandmarks);

//     // In ra các tọa độ landmark của miệng để kiểm tra
//     std::cout << "Mouth Landmarks:" << std::endl;
//     for (cv::Point point : mouthLandmarks) {
//         std::cout << point << ", " << std::endl;
//     }

//     return 0;
// }

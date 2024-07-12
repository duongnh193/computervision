#include <godot_cpp/classes/node2d.hpp>
#include"facedetect.h"

int main(int argc, char *argv[])
{
    FaceDetect faceDetect;
    faceDetect.modelPath = "/home/duongnh/SourceCode/yolov8_detection1.onnx";
    faceDetect.modelShape = cv::Size(640,640);
    faceDetect.InitEngine();

    cv::Mat frame;
    cv::VideoCapture cap;
    int deviceID = 0; // 0 = open default camera
    int apiID = cv::CAP_ANY; // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    std::cout << "Start grabbing" << std::endl
              << "Press any key to terminate" << std::endl;
    while(true)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        auto faces = faceDetect.InferenceEngine(frame);
        if (faces.empty()) {
            cv::putText(frame, "No face detected", cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        } else {
            for (cv::Rect &rect : faces){
                cv::rectangle(frame, rect, cv::Scalar(0,0,255),2);
            }
            std::string numFaces = std::to_string(faces.size()) + " face detected";
            cv::putText(frame, numFaces, cv::Point(50, 50), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 0), 2);
        }
        imshow("Frame", frame);
        if (cv::waitKey(1) >= 0){
            break;
        }
    }
}

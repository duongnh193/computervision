#include "facelandmark.h"
#include <iostream>


#define FACE_LANDMARKS 468
/*
Helper function
*/
bool __isIndexValid(int idx) {
    if (idx < 0 || idx >= FACE_LANDMARKS) {
        std::cerr << "Index " << idx << " is out of range (" \
                  << FACE_LANDMARKS << ")." << std::endl;
        return false;
    }
    return true;
}


my::FaceLandmark::FaceLandmark(std::string modelPath):
    FaceDetection(modelPath),
    m_landmarkModel(modelPath + std::string("/face_landmark.tflite"))
{}


void my::FaceLandmark::runInference() {
    FaceDetection::runInference();
    auto roi = FaceDetection::getFaceRoi();
    if (roi.empty()) return;

    auto face = FaceDetection::cropFrame(roi);
    m_landmarkModel.loadImageToInput(face);
    m_landmarkModel.runInference();


}


cv::Point my::FaceLandmark::getFaceLandmarkAt(int index) const {
    if (__isIndexValid(index)) {
        auto roi = FaceDetection::getFaceRoi();


        float _x = m_landmarkModel.getOutputData()[index * 3];
        float _y = m_landmarkModel.getOutputData()[index * 3 + 1];

        int x = (int)(_x / m_landmarkModel.getInputShape()[2] * roi.width) + roi.x;
        int y = (int)(_y / m_landmarkModel.getInputShape()[1] * roi.height) + roi.y;

        return cv::Point(x,y);
    }
    return cv::Point();
}


std::vector<cv::Point> my::FaceLandmark::getMouthLandmarks() const {
    if (FaceDetection::getFaceRoi().empty())
        return std::vector<cv::Point>();

    std::vector<cv::Point> mouthLandmarks;

    std::vector<int> lipsOuter{
        // lipsUpperOuter
        61, 185, 40, 39, 37, 0, 267, 269, 270, 409, 291,
        // lipsLowerOuter in reverse order
        375, 321, 405, 314, 17, 84, 181, 91, 146, 61
    };

    // std::vector<int> lipsInner{
    //     // lipsUpperInner
    //     78, 191, 80, 81, 82, 13, 312, 311, 310, 415, 308,
    //     // lipsLowerOuter in reverse order
    //     324, 318, 402, 317, 14, 87, 178, 88, 95, 78
    // };

    for (int index : lipsOuter) {
        mouthLandmarks.push_back(getFaceLandmarkAt(index));
    };

    // for (int index : lipsInner) {
    //     mouthLandmarks.push_back(getFaceLandmarkAt(index));
    // };

    return mouthLandmarks;
}


std::vector<float> my::FaceLandmark::loadOutput(int index) const {
    return m_landmarkModel.loadOutput();
}

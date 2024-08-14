#include "detectionpostprocess.h"
#include <iostream>

/*
Helper function
*/
std::vector<cv::Rect2f> generateAnchors(my::AnchorOptions options) {
    std::vector<cv::Rect2f> anchors;
    for (int i = 0; i < NUM_SIZES; ++i) {
        auto size = options.sizes[i];
        auto numLayer = options.numLayers[i];

        for (auto y = 0; y < size; ++y) {
            for (auto x = 0; x < size; ++x) {
                float x_center = (x + options.offsetX) * 1.f / size;
                float y_center = (y + options.offsetY) * 1.f / size;
                float w = 1.f;
                float h = 1.f;
                anchors.insert(anchors.end(), numLayer, cv::Rect2f(x_center - w/2.f, y_center - h/2.f, w, h));
            }
        }
    }
    return anchors;
}


my::DetectionPostProcess::DetectionPostProcess() :
    m_anchors(generateAnchors(AnchorOptions())) {}


cv::Rect2f my::DetectionPostProcess::decodeBox
    (const std::vector<float>& rawBoxes, int index) const {
    auto anchor = m_anchors[index];
    auto center = (anchor.tl() + anchor.br()) * 0.5;

    auto boxOffset = index * NUM_COORD;
    float cx = rawBoxes[boxOffset];
    float cy = rawBoxes[boxOffset + 1];
    float w = rawBoxes[boxOffset + 2];
    float h = rawBoxes[boxOffset + 3];

    cx = cx / DETECTION_SIZE * anchor.width + center.x;
    cy = cy / DETECTION_SIZE * anchor.height + center.y;
    w = w / DETECTION_SIZE * anchor.width;
    h = h / DETECTION_SIZE * anchor.height;

    return cv::Rect2f(cx - w/2, cy - h/2, w, h);
}

std::vector<my::Detection> my::DetectionPostProcess::getHighestScoreDetections(const std::vector<float>& rawBoxes, const std::vector<float>& scores, uint faceNum) const {
    std::vector<my::Detection> result;
    for (int i = 0; i < NUM_BOXES; i++) {
        //so sanh voi threshold
        if(scores[i] >MIN_THRESHOLD){
            if(result.size() < faceNum){
                auto data = decodeBox(rawBoxes, i);
                result.push_back(my::Detection(scores[i], CLASS_ID, data));
            } else {
                int iMin = 0;
                if(scores[iMin] < scores[i]) {
                    iMin = i;
                }
                auto data = decodeBox(rawBoxes,i);
                result.push_back(my::Detection(scores[i], CLASS_ID, data));
            }
        }
    }
    return result;
}

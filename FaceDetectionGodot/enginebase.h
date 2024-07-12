#ifndef ENGINEBASEDETECT_H
#define ENGINEBASEDETECT_H
#include <QDebug>
#include "utils.h"
#include <string>
#include <onnxruntime_cxx_api.h>
class EngineBase
{
public:
    EngineBase();
    virtual void InitEngine();
    virtual std::vector<float> InferenceEngine(cv::Mat &image){};
    virtual cv::Mat PreprocessImage(cv::Mat &image){};
    std::vector<std::string> labels;
    Ort::Session *engine;
    Ort::Env env;
    Ort::SessionOptions sessionOption;
    //setting
    int numThread;
    std::string modelPath;
    cv::Size modelShape;
    std::vector<int64_t> inputNodeDims;
    float objectThreshold = 0.5;
    float IouThreshold = 0.45;
protected:
    float ratio=1;
    std::vector<const char*> inputNames;
    std::vector<const char*> outputNames;
};


#endif // ENGINEBASEDETECT_H



#include "enginebase.h"

EngineBase::EngineBase() {
    modelShape = cv::Size(640,640);
    inputNodeDims= {1,3,640, 640};
}

void EngineBase::InitEngine()
{
    LOG_C("from base class");
    env = Ort::Env(ORT_LOGGING_LEVEL_WARNING, "Vivas");
    sessionOption.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
    sessionOption.SetIntraOpNumThreads(numThread);
    sessionOption.SetLogSeverityLevel(ORT_LOGGING_LEVEL_WARNING);
    engine = new Ort::Session(env, modelPath.c_str(),sessionOption);
    LOG_C("init done");
}

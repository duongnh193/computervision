#include "facedetect.h"
#include <iostream>


FaceDetect::FaceDetect() {}

// void FaceDetect::_bind_methods() {
//     godot::ClassDB::bind_method(godot::D_METHOD("InitEngine"), &FaceDetect::InitEngine);
//     godot::ClassDB::bind_method(godot::D_METHOD("InferenceEngine", "image"), &FaceDetect::InferenceEngine);
//     // godot::ClassDB::add_property("FaceDetect", godot::PropertyInfo(godot::Variant::FLOAT, "InitEngine"), "InitEngine", "InferenceEngine");
// }

void FaceDetect::InitEngine()
{
    runOption = Ort::RunOptions{nullptr};
    EngineBase::InitEngine();
    Ort::AllocatorWithDefaultOptions allocator;
    uint inputCount = engine->GetInputCount();
    for (size_t i = 0; i < inputCount; i++) {
        Ort::AllocatedStringPtr inputNodeName = engine->GetInputNameAllocated(i, allocator);
        char *temp_buf = new char[50];
        strcpy(temp_buf, inputNodeName.get());
        inputNames.push_back(temp_buf);
    }
    uint outputCount = engine->GetOutputCount();
    for (size_t i = 0; i < outputCount; i++) {
        Ort::AllocatedStringPtr outNames = engine->GetOutputNameAllocated(i, allocator);
        char *temp_buf = new char[50];
        strcpy(temp_buf, outNames.get());
        outputNames.push_back(temp_buf);
    }
}

std::vector<cv::Rect> FaceDetect::InferenceEngine(cv::Mat image)
{
    cv::Mat preprocessImg = PreprocessImage(image);
    cv::Mat blobImg = cv::dnn::blobFromImage(preprocessImg,NORM);
    float *imgData = (float*) blobImg.data;

    Ort::Value inputTensor = Ort::Value::CreateTensor<typename std::remove_pointer<float*>::type>(
        Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator,OrtMemTypeCPU), imgData, 3 * modelShape.height * modelShape.width,
        inputNodeDims.data(),inputNodeDims.size());
    auto sessionResult = engine->Run(runOption, inputNames.data(), &inputTensor, inputNames.size(),outputNames.data(), outputNames.size());
    Ort::TypeInfo typeInfo = sessionResult.front().GetTypeInfo();
    auto tensor_info = typeInfo.GetTensorTypeAndShapeInfo();
    std::vector<int64_t> outputNodeDims = tensor_info.GetShape();
    auto outputData = sessionResult.front().GetTensorMutableData<typename std::remove_pointer<float*>::type>();
    LOG_C(outputNodeDims.size());
    cv::Mat output = cv::Mat(outputNodeDims[1], outputNodeDims[2], CV_32F, outputData);
    output = output.t();
    LOG_C("width: " << output.cols << " height: " << output.rows);

    return PosprocessImage(image,output);
}

cv::Mat FaceDetect::PreprocessImage(cv::Mat &image)
{
    int maxSize = image.cols > image.rows ? image.cols : image.rows;
    cv::Mat result(maxSize, maxSize, image.type());
    image.copyTo(result(cv::Rect(0,0,image.cols, image.rows)));
    cv::cvtColor(result,result,cv::COLOR_BGR2RGB);
    cv::resize(result,result, modelShape);
    return result;
}

std::vector<cv::Rect> FaceDetect::PosprocessImage(cv::Mat &image, cv::Mat &sessionResult)
{
    std::vector<cv::Rect> results;
    LOG_C(sessionResult.cols << " " << sessionResult.rows);
    float* data = (float*)sessionResult.data;
    float factor =  image.cols > image.rows ? (float)image.cols/modelShape.width : (float)image.rows/modelShape.height;
    for (int i = 0; i < sessionResult.rows; i++) {
        cv::Mat row = sessionResult.row(i);
        // LOG_C(row);
        float confidence = row.at<float>(0,4);
        if(confidence >objectThreshold){
            // LOG_C("confidence: "<<confidence);
            cv::Rect rect;
            float x = row.at<float>(0,0);
            float y = row.at<float>(0,1);
            float w = row.at<float>(0,2);
            float h = row.at<float>(0,3);

            //            LOG_INFO << "x y w h: " << x << " " << y << " "<< w << " " << h;
            rect.x = float((x - 0.5 * w) * factor);
            rect.y = float((y - 0.5 * h) * factor);

            rect.width = float(w * factor);
            rect.height = float(h * factor);
            //            LOG_INFO << "facetor: " << factor << " " << image.size;
            //correct
            rect.x = MAX(rect.x, 0);
            rect.y = MAX(rect.y,0);
            rect.width = MIN(rect.width, image.cols - rect.x);
            rect.height = MIN(rect.height, image.rows - rect.y);
            results.push_back(rect);
        }
    }
    LOG_C("Result size: "<< results.size());
    if (results.size() > 0){
        NMS(results);
    }
    LOG_C("Result size: "<< results.size());
    return results;
}

void FaceDetect::NMS(std::vector<cv::Rect> &rects)
{
    sort(rects.begin(), rects.end(),[](cv::Rect a, cv::Rect b){
        return a.area() > b.area();
    });
    std::vector<cv::Rect> results;
    // bool overlap =false;
    cv::Rect2f intersec;
    cv::Rect2f uni;
    float IOU;
    for(uint i = 0; i< rects.size()-1; i++){
        // overlap =false;
        for(uint j= i+1; j<rects.size();){
            intersec = rects[i] & rects[j];
            uni = rects[i] | rects[j];
            IOU = (float)intersec.area()/uni.area();
            if (IOU > IouThreshold){
                rects.erase(rects.begin()+j);
                continue;
            }
            j++;

        }
    }


}





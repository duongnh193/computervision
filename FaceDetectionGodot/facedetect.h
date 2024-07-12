#ifndef FACEDETECT_H
#define FACEDETECT_H
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>
#include "enginebase.h"

    class FaceDetect : public EngineBase
        {
        // GDCLASS(FaceDetect, godot::Node2D)
        public:
            FaceDetect();
            // EngineBase interface
            void InitEngine() override;
            std::vector<cv::Rect> InferenceEngine(cv::Mat image);
            cv::Mat PreVideo(cv::Mat frame, cv::VideoCapture cap);

        // protected:
        //    static void _bind_methods();

        private:
            cv::Mat PreprocessImage(cv::Mat &image) override;
            std::vector<cv::Rect> PosprocessImage(cv::Mat &image, cv::Mat &sessionResult);
            void NMS(std::vector<cv::Rect> &rects);
        private:
            Ort::RunOptions runOption;
        };


#endif // FACEDETECT_H

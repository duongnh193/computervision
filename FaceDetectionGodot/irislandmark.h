// #ifndef IRISLANDMARK_H
// #define IRISLANDMARK_H
// #include <godot_cpp/classes/node2d.hpp>
// #include <godot_cpp/classes/input.hpp>
// #include <godot_cpp/classes/engine.hpp>
// #include "facelandmark.h"
// #include <bitset>
// #include <opencv2/highgui.hpp>

// namespace my {

// class IrisLandmark: public my::FaceLandmark, godot::Node2D {
//     GDCLASS(IrisLandmark, godot::Node2D)
// public:
//     /*
//             Users MUST provide the FOLDER contain ALL the face_detection_short.tflite,
//             face_landmark.tflite and iris_landmark.tflite
//             */
//     IrisLandmark(std::string modelPath);
//     virtual ~IrisLandmark() = default;
//     void _process(double delta) override;


// protected:
//     static void _bind_methods();
// };
// }
// #endif // IRISLANDMARK_H

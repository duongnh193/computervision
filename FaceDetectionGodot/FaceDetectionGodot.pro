QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        detectionpostprocess.cpp \
        facedetection.cpp \
        facelandmark.cpp \
        irislandmark.cpp \
        main.cpp \
        modelloader.cpp \
        registertypes.cpp \
    test.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /usr/local/include/opencv4/
LIBS += -L/usr/local/lib/ -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_dnn -lopencv_objdetect -lopencv_videoio
INCLUDEPATH += /home/duongnh/Downloads/onnxruntime-linux-x64-gpu-1.18.0/include/
LIBS += -L/home/duongnh/Downloads/onnxruntime-linux-x64-gpu-1.18.0/lib -lonnxruntime
INCLUDEPATH += /home/duongnh/Projects/Godot/gdextension_cpp_example/godot-cpp/gen/include/
INCLUDEPATH += /home/duongnh/Projects/Godot/gdextension_cpp_example/godot-cpp/include/
INCLUDEPATH += /home/duongnh/Projects/Godot/gdextension_cpp_example/godot-cpp/gdextension/
LIBS += -L/home/duongnh/Projects/Godot/gdextension_cpp_example/godot-cpp/bin/ -lgodot-cpp.linux.template_debug.x86_64

INCLUDEPATH += /home/duongnh/Downloads/tflite/tflite-dist/include/
LIBS += -L/home/duongnh/Downloads/tflite/tflite-dist/libs/linux_x64 -ltensorflowlite

`

HEADERS += \
    detectionpostprocess.h \
    facedetection.h \
    facelandmark.h \
    irislandmark.h \
    modelloader.h \
    registertypes.h \
    test.h

DISTFILES += \
    SConstruct.py \
    build/Desktop_Qt_6_7_1-Debug/FaceDetectionGodot

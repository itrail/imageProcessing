TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

INCLUDEPATH += "C:\OpenCV345\install\include"

LIBS += -LC:\OpenCV345\install\x64\mingw\bin\
    -lopencv_core345 \
    -lopencv_highgui345 \
    -lopencv_imgcodecs345 \
    -lopencv_imgproc345 \
    -lopencv_video345 \
    -lopencv_videoio345 \
    -lopencv_calib3d345

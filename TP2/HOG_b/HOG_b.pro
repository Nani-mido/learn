#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T00:05:24
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = HOG_b
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Hog.cpp


INCLUDEPATH += D:\\softwares\\OpenCV\\OpenCV-2.4.10\\build_opnecv_qt\\install\\include
INCLUDEPATH += D:\\softwares\\OpenCV\\OpenCV-2.4.10\\build_opnecv_qt\\install\\include\\opencv

LIBS += -LD:\\softwares\\OpenCV\\OpenCV-2.4.10\\build_opnecv_qt\\install\\x64\\mingw\\bin \
    -lopencv_calib3d2410d \
    -lopencv_contrib2410d \
    -lopencv_core2410d \
    -lopencv_features2d2410d \
    -lopencv_flann2410d \
    -lopencv_gpu2410d \
    -lopencv_highgui2410d \
    -lopencv_imgproc2410d \
    -lopencv_legacy2410d \
    -lopencv_ml2410d \
    -lopencv_nonfree2410d \
    -lopencv_objdetect2410d \
    -lopencv_photo2410d \
    -lopencv_stitching2410d \
    -lopencv_superres2410d \
    -lopencv_video2410d \
    -lopencv_videostab2410d

HEADERS += \
    Hog.hpp

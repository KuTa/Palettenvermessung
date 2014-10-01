#-------------------------------------------------
#
# Project created by QtCreator 2014-08-29T14:44:41
#
#-------------------------------------------------

QT       += core gui  #opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11
DEPENDS += "/home/kuschan/build-OpenGLPro-Desktop-Debug/"
TARGET = OpenGLPro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        grabber.cpp

HEADERS  += mainwindow.h\
        grabber.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lpcl_common
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lpcl_common
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lpcl_common

INCLUDEPATH += $$PWD/../../../../usr/local/include/pcl-1.8\
                /usr/include/eigen3
DEPENDPATH += $$PWD/../../../../usr/local/include/pcl-1.8

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lpcl_io
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lpcl_io
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lpcl_io

INCLUDEPATH += $$PWD/../../../../usr/local/include/pcl-1.8
DEPENDPATH += $$PWD/../../../../usr/local/include/pcl-1.8


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lpcl_filters
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lpcl_filters
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lpcl_filters

INCLUDEPATH += $$PWD/../../../../usr/local/include/pcl-1.8
DEPENDPATH += $$PWD/../../../../usr/local/include/pcl-1.8

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lpcl_visualization
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lpcl_visualization
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lpcl_visualization

INCLUDEPATH += $$PWD/../../../../usr/local/include/pcl-1.8
DEPENDPATH += $$PWD/../../../../usr/local/include/pcl-1.8

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lvtkHybrid
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lvtkHybrid
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lvtkHybrid

INCLUDEPATH += $$PWD/../../../../usr/include/vtk-5.8
DEPENDPATH += $$PWD/../../../../usr/include/vtk-5.8



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lvtkGraphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lvtkGraphics
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lvtkGraphics

INCLUDEPATH += $$PWD/../../../../usr/include/vtk-5.8
DEPENDPATH += $$PWD/../../../../usr/include/vtk-5.8

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lvtkRendering
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lvtkRendering
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lvtkRendering

INCLUDEPATH += $$PWD/../../../../usr/include/vtk-5.8
DEPENDPATH += $$PWD/../../../../usr/include/vtk-5.8


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lQVTK
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lQVTK
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lQVTK

INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH += $$PWD/../../../../usr/include



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/arm-linux-gnueabihf/release/ -lboost_system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/arm-linux-gnueabihf/debug/ -lboost_system
else:unix: LIBS += -L$$PWD/../../../../usr/lib/arm-linux-gnueabihf/ -lboost_system

INCLUDEPATH += $$PWD/../../../../usr/include/boost
DEPENDPATH += $$PWD/../../../../usr/include/boost

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lvtkCommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lvtkCommon
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lvtkCommon

INCLUDEPATH += $$PWD/../../../../usr/include/vtk-5.8
DEPENDPATH += $$PWD/../../../../usr/include/vtk-5.8

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lvtkFiltering
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lvtkFiltering
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lvtkFiltering

INCLUDEPATH += $$PWD/../../../../usr/include/vtk-5.8
DEPENDPATH += $$PWD/../../../../usr/include/vtk-5.8



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OpenNI2/Bin/x64-Release/release/ -lOpenNI2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OpenNI2/Bin/x64-Release/debug/ -lOpenNI2
else:unix: LIBS += -L$$PWD/../OpenNI2/Bin/x64-Release/ -lOpenNI2

INCLUDEPATH += $$PWD/../OpenNI2/Include
DEPENDPATH += $$PWD/../OpenNI2/Include


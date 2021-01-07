QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainFunctions.cpp \
    mainwindow.cpp \
    util.cpp

HEADERS += \
    mainwindow.h \
    util.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#OPENCV_START
INCLUDEPATH += /usr/local/include/opencv4
LIBS += -L/usr/local/lib \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgproc \
    -lopencv_features2d \
    -lopencv_xfeatures2d \
    -lopencv_calib3d \
    -lopencv_video \
    -lopencv_videoio \
    -lopencv_imgcodecs \
    -lopencv_objdetect
#OpenCV_END

RESOURCES += \
    resources.qrc

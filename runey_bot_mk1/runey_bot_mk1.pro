QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Conditions/chanceCondition.cpp \
    Conditions/imageCondition.cpp \
    Conditions/pixelsCondition.cpp \
    Conditions/stateCondition.cpp \
    Conditions/tabCondition.cpp \
    Conditions/timeoutCondition.cpp \
    Modules/module.cpp \
    Tasks/antiBanTask.cpp \
    Tasks/changeTabTask.cpp \
    Tasks/clickAreaTask.cpp \
    Tasks/clickHighlightTask.cpp \
    Tasks/clickImagesTask.cpp \
    Tasks/clickItemsTask.cpp \
    Tasks/delayTask.cpp \
    Tasks/keyboardTask.cpp \
    Tasks/setStateTask.cpp \
    Tasks/takeBreakTask.cpp \
    Tasks/timerTask.cpp \
    Tasks/useItemsTask.cpp \
    botFactory.cpp \
    botInstance.cpp \
    botinfo.cpp \
    Conditions/inventoryCondition.cpp \
    keyboardController.cpp \
    main.cpp \
    mainFunctions.cpp \
    mainwindow.cpp \
    mouseController.cpp \
    timer.cpp \
    util.cpp

HEADERS += \
    Conditions/chanceCondition.h \
    Conditions/condition.h \
    Conditions/imageCondition.h \
    Conditions/pixelsCondition.h \
    Conditions/stateCondition.h \
    Conditions/tabCondition.h \
    Conditions/timeoutCondition.h \
    Modules/module.h \
    Tasks/antiBanTask.h \
    Tasks/changeTabTask.h \
    Tasks/clickAreaTask.h \
    Tasks/clickHighlightTask.h \
    Tasks/clickImagesTask.h \
    Tasks/clickItemsTask.h \
    Tasks/delayTask.h \
    Tasks/keyboardTask.h \
    Tasks/setStateTask.h \
    Tasks/takeBreakTask.h \
    Tasks/timerTask.h \
    Tasks/useItemsTask.h \
    botFactory.h \
    botInstance.h \
    botinfo.h \
    Conditions/inventoryCondition.h \
    defines.h \
    keyboardController.h \
    mainwindow.h \
    mouseController.h \
    sleeper.h \
    Tasks/task.h \
    timer.h \
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

# XDoTool >___ (Local install) sudo make, sudo make install (sudo apt-get install libxkbcommon-dev)
#
INCLUDEPATH += /usr/bin
DEPENDPATH += /usr/bin

LIBS += -L/usr/bin -lxdo
#XDoTool!

RESOURCES += \
    imageResources.qrc


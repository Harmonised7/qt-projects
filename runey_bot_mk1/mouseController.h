#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

//Mouse Controller
#define MOUSE_JITTER    5
#define MOUSE_FPS       120
#define MOUSE_MIN       0.01
#define MOUSE_MAX       0.025
#define MOUSE_CURVES    2
#define MOUSE_SCREEN    0

// Qt Native Includes //
#include <QPoint>
#include <QRect>
#include <QCursor>
#include <QThread>
#include <QApplication>
#include <QDesktopWidget>
#include <QCursor>

// User written Includes //
#include "sleeper.h"
#include "util.h"

enum class MouseStates
{
    Left,
    Right,
    Middle
};

class MouseController
{
public:
    MouseController( const uint &mouseFPS, const double &minSpeed, const double &maxSpeed, const int &jitter, const int &curves, const int &mouseScreen);
    ~MouseController();

    void changeRandValues();

    void pressESC();

    void mouseMove(const int &newX, const int &newY);
    void mouseMove(const QPoint &newPoint);

    void mousePress(const MouseStates &state, const int &newX, const int &newY, const int &timeSleepMin, const int &timeSleepMax);
    void mousePress(const MouseStates &state, const QPoint &newPoint, const int &timeSleepMin, const int &timeSleepMax);

    void mouseDrag(const MouseStates &state, const int &newX, const int &newY, const int &timeSleepMin, const int &timeSleepMax);
    void mouseDrag(const MouseStates &state, const QPoint &newPoint, const int &timeSleepMin, const int &timeSleepMax);

    void changeFPS(const uint &newFPS);
    uint getFPS();

    void changeJitter(const int &newJitterVal);
    void resetJitter();
    int getJitterVal();

    void changeSpeed(const double &newSpeedVal, const double &newMinSpeedVal);
    void resetSpeed();

    static QPoint getMousePos();
    static double measureDistance(const QPoint &pA, const QPoint &pB);

    static MouseController mc;

private:
    int _jitterValue;
    uint _mouseFPS;

    double _minSpeed;
    double _maxSpeed;

    int _curves;

    QPoint _p0;
    QPoint _p1;
    QPoint _p1Goal;
    QPoint _p2;
    QPoint _pFinal;

    double _t;
    double _tSpeed;

    int _mouseScreen;
};

#endif // MOUSECONTROLLER_H

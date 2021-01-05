#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

// Qt Native Includes //
#include <QPoint>
#include <QRect>
#include <QCursor>
#include <QThread>
#include <QApplication>
#include <QDesktopWidget>
#include <QCursor>

// User written Includes //
#include "rndController.h"
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
    int getJitterVal();

    void changeSpeed(const double &newSpeedVal, const double &newMinSpeedVal);

    static QPoint getMousePos();
    static double measureDistance(const QPoint &pA, const QPoint &pB);

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

    RndController *_randomNumbers;
};

#endif // MOUSECONTROLLER_H

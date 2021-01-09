#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

//Mouse Controller
#define MOUSE_JITTER        4
#define MOUSE_CURVES_MIN    3
#define MOUSE_CURVES_MAX    60
#define MOUSE_FPS           120
#define MOUSE_SPEED_MIN     0.0025
#define MOUSE_SPEED_MAX     0.0075
#define SCREEN              0
#define MOUSE_DELAY_MIN     50
#define MOUSE_DELAY_MAX     85

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
    MouseController( int screen );
    ~MouseController();

    void changeRandValues();

    void pressESC();

    void mouseMoveRelative( QPoint p );
    void mouseMoveRelative( int relativeX, int relativeY );
    void mouseMove(QPoint newPoint);
    void mouseMove(int newX, int newY);

    void mousePressRelative( MouseStates state, QPoint p );
    void mousePressRelative( MouseStates state, int relativeX, int relativeY );
    void mousePress( MouseStates state, QPoint newPoint );
    void mousePress( MouseStates state, int newX, int newY );

    void mouseDragRelative( MouseStates state, QPoint p );
    void mouseDragRelative( MouseStates state, int relativeX, int relativeY );
    void mouseDrag( MouseStates state, QPoint newPoint );
    void mouseDrag( MouseStates state, int newX, int newY );

    void setFPS(uint newFPS);
    uint getFPS();

    void setJitter(int newJitterVal);
    void resetJitter();
    int getJitterVal();

    void setSpeed( double newSpeed, double newMinSpeed );
    void resetSpeed();

    void setClickDelay(double newMaxDelay, double newMinDelay );
    void resetClickDelay();

    static QPoint getMousePos();
    static double measureDistance(QPoint pA, QPoint pB);

    static MouseController mc;

private:
    int _jitterValue;
    uint _mouseFPS;

    double _minSpeed;
    double _maxSpeed;

    int _minDelay;
    int _maxDelay;

    int _minCurves;
    int _maxCurves;

    QPoint _p0;
    QPoint _p1;
    QPoint _p1Goal;
    QPoint _p2;
    QPoint _pFinal;

    double _t;
    double _tSpeed;

    int _screen;
};

#endif // MOUSECONTROLLER_H

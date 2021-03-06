#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

//Mouse Controller
#define MOUSE_JITTER            4
#define MOUSE_CURVES_MIN        1
#define MOUSE_CURVES_MAX        60
#define MOUSE_FPS               120
#define MOUSE_SPEED_MIN         0.0025
#define MOUSE_SPEED_MAX         0.0075
#define MOUSE_CLICK_DELAY_MIN   50
#define MOUSE_CLICK_DELAY_MAX   85
#define MOUSE_RELEASE_DELAY_MIN 5
#define MOUSE_RELEASE_DELAY_MAX 65
#define MOUSE_HIJACK_FOR        2500

// Qt Native Includes
#include <QPoint>
#include <QRect>
#include <QCursor>
#include <QThread>
#include <QApplication>
#include <QCursor>

//Util Includes
#include "Util/sleeper.h"
#include "Util/util.h"

enum class MouseState
{
    Left = 1,
    Middle = 2,
    Right = 3
};

class MouseController
{
public:
    ~MouseController();

    void changeRandValues();

    void pressESC();

    void mouseMoveRelative( QPoint p );
    void mouseMoveRelative( int relativeX, int relativeY );
    void mouseMove(QPoint newPoint);
    void mouseMove(int newX, int newY);

    void mousePressRelative( MouseState state, QPoint p );
    void mousePressRelative( MouseState state, int relativeX, int relativeY );
    void mousePress( MouseState state, QPoint newPoint );
    void mousePress( MouseState state, int newX, int newY );
    void mousePress( MouseState state );

    void mouseDragRelative( MouseState state, QPoint p );
    void mouseDragRelative( MouseState state, int relativeX, int relativeY );
    void mouseDrag( MouseState state, QPoint newPoint );
    void mouseDrag( MouseState state, int newX, int newY );

    void setFPS(uint newFPS);
    uint getFPS();

    void setJitter(int newJitterVal);
    void resetJitter();
    int getJitterVal();

    void setSpeed( double newSpeed, double newMinSpeed );
    void resetSpeed();

    void setClickDelay(double newMaxDelay, double newMinDelay );
    void resetClickDelay();

    void setHijacked();

    bool mouseHijacked();

    static QPoint getMousePos();

    static MouseController mc;

private:
    MouseController( int screen );

    int _lastX, _lastY;
    unsigned long _hijackSince;

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

    unsigned long totalClicks = 0;
};

#endif // MOUSECONTROLLER_H

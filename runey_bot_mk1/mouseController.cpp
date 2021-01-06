#include "mouseController.h"

extern "C"
{
#include "xdo.h"
}

MouseController MouseController::_mc = MouseController( MOUSE_FPS, MOUSE_MIN, MOUSE_MAX, (double) MOUSE_JITTER, MOUSE_CURVES, MOUSE_SCREEN );
static xdo_t *xDoTool;

MouseController::MouseController( const uint &mouseFPS, const double &minSpeed, const double &maxSpeed, const int &jitter, const int &curves, const int &mouseScreen) :
    _jitterValue(jitter),
    _mouseFPS(mouseFPS),
    _minSpeed(minSpeed),
    _maxSpeed(maxSpeed),
    _curves(curves),
    _p0(0, 0),
    _p1(0, 0),
    _p1Goal(0, 0),
    _p2(0, 0),
    _tSpeed( Util::mapCapped(measureDistance(_p0, _p2), 0, 500, _maxSpeed, _minSpeed) ),
    _mouseScreen(mouseScreen),
    _randomNumbers(new RndController)
{
    xDoTool = xdo_new(nullptr);

    qDebug() << "Initialized Mouse Controller...";
}

MouseController::~MouseController()
{
    xdo_free( xDoTool );
}

void MouseController::changeRandValues()
{
    _jitterValue = RndController::genRandDouble( 1, 100 );
    _curves = RndController::genRandDouble( 1, 100 );
}

void MouseController::mouseMove( const int &newX, const int &newY )
{
//    changeRandValues();

    _p0 = getMousePos();
    _p2.setX( newX );
    _p2.setY( newY );
    _p1 = QPoint( RndController::genRand( _p0.x(), _p2.x() ), RndController::genRand( _p0.y(), _p2.y() ) );

    _p1Goal.setX( (_p0.x() + _p2.x()) / 2 + RndController::genRand(-_curves * 5, _curves * 5) );
    _p1Goal.setY( (_p0.y() + _p2.y()) / 2 + RndController::genRand(-_curves * 5, _curves * 5) );

    for (_t = 0; _t <= 1; _t += _tSpeed)
    {
        if (_p1.x() < _p1Goal.x())
            _p1.setX(_p1.x() + RndController::genRand(_jitterValue));
        else
            _p1.setX(_p1.x() - RndController::genRand(_jitterValue));

        if (_p1.y() < _p1Goal.y())
            _p1.setY(_p1.y() + RndController::genRand(_jitterValue));
        else
            _p1.setY(_p1.y() - RndController::genRand(_jitterValue));

        if ( floor(RndController::genRand(1, 30)) == 1 )
        {
            _p1Goal.setX( (_p0.x() + _p2.x()) / 2 + RndController::genRand(-_curves * 3, _curves * 3) );
            _p1Goal.setY( (_p0.y() + _p2.y()) / 2 + RndController::genRand(-_curves * 3, _curves * 3) );
        }

        _tSpeed = ( Util::mapCapped(measureDistance(_p0, _p2), 0, 500, _maxSpeed, _minSpeed) );

        if (_tSpeed < 0.003)
            _tSpeed = RndController::genRandDouble(_minSpeed, _maxSpeed);

        _t += RndController::genRandDouble(_tSpeed, _tSpeed * 1.5);

        if (_t > 1)
            _t = 1;

        qDebug() << _t;

        _pFinal.setX( static_cast<int>((pow((1.0 - _t), 2) * (_p0.x()) + (1.0 - _t) * 2.0 * _t * (_p1.x()) + _t * _t * (_p2.x()))) );
        _pFinal.setY( static_cast<int>((pow((1.0 - _t), 2) * (_p0.y()) + (1.0 - _t) * 2.0 * _t * (_p1.y()) + _t * _t * (_p2.y()))) );

        QCursor::setPos( _pFinal.x(), _pFinal.y() );

        Sleeper::msleep(1000 / _mouseFPS);
    }
}

QPoint MouseController::getMousePos()
{
    int x, y, screen;
    xdo_get_mouse_location(xDoTool, &x, &y, &screen);
    return QPoint(x, y);
}

void MouseController::mouseMove(const QPoint &newPoint)
{
    mouseMove(newPoint.x(), newPoint.y());
}

void MouseController::mousePress(const MouseStates &state, const int &newX, const int &newY, const int &timeSleepMin, const int &timeSleepMax)
{
    mouseMove(newX, newY);

    if (state == MouseStates::Left)
    {
        xdo_mouse_down(xDoTool, CURRENTWINDOW, Button1);
        Sleeper::msleep( static_cast<uint>(RndController::genRand(timeSleepMin, timeSleepMax)) );
        xdo_mouse_up(xDoTool, CURRENTWINDOW, Button1);
    }
    else if (state == MouseStates::Right)
    {
        xdo_mouse_down(xDoTool, CURRENTWINDOW, Button3);
        Sleeper::msleep( static_cast<uint>(RndController::genRand(timeSleepMin, timeSleepMax)) );
        xdo_mouse_up(xDoTool, CURRENTWINDOW, Button3);
    }
    else if (state == MouseStates::Middle)
    {
        xdo_mouse_down(xDoTool, CURRENTWINDOW, Button2);
        Sleeper::msleep( static_cast<uint>(RndController::genRand(timeSleepMin, timeSleepMax)) );
        xdo_mouse_up(xDoTool, CURRENTWINDOW, Button2);
    }
}

void MouseController::mousePress(const MouseStates &state, const QPoint &newPoint, const int &timeSleepMin, const int &timeSleepMax)
{
    mousePress(state, newPoint.x(), newPoint.y(), timeSleepMin, timeSleepMax);
}

void MouseController::mouseDrag(const MouseStates &state, const int &newX, const int &newY, const int &timeSleepMin, const int &timeSleepMax)
{
    qDebug() << "Dragging to x:" << newX << " y:" << newY;
    if (state == MouseStates::Left)
    {
        xdo_mouse_down(xDoTool, CURRENTWINDOW, Button1);
        Sleeper::msleep( static_cast<uint>(RndController::genRand(timeSleepMin, timeSleepMax)) );
    }
    else if (state == MouseStates::Right)
    {
        xdo_mouse_down(xDoTool, CURRENTWINDOW, Button3);
        Sleeper::msleep( static_cast<uint>(RndController::genRand(timeSleepMin, timeSleepMax)) );
    }
    else if (state == MouseStates::Middle)
    {
        xdo_mouse_down(xDoTool, CURRENTWINDOW, Button2);
        Sleeper::msleep( static_cast<uint>(RndController::genRand(timeSleepMin, timeSleepMax)) );
    }

    mouseMove(newX, newY);

    if (state == MouseStates::Left)
    {
        Sleeper::msleep( static_cast<uint>(RndController::genRand(timeSleepMin, timeSleepMax)) );
        xdo_mouse_up(xDoTool, CURRENTWINDOW, Button1);
    }
    else if (state == MouseStates::Right)
    {
        Sleeper::msleep( static_cast<uint>(RndController::genRand(timeSleepMin, timeSleepMax)) );
        xdo_mouse_up(xDoTool, CURRENTWINDOW, Button3);
    }
    else if (state == MouseStates::Middle)
    {
        Sleeper::msleep( static_cast<uint>(RndController::genRand(timeSleepMin, timeSleepMax)) );
        xdo_mouse_up(xDoTool, CURRENTWINDOW, Button2);
    }
}

void MouseController::mouseDrag(const MouseStates &state, const QPoint &newPoint, const int &timeSleepMin, const int &timeSleepMax)
{
    mouseDrag(state, newPoint.x(), newPoint.y(), timeSleepMin, timeSleepMax);
}

void MouseController::changeFPS(const uint &newFPS)
{
    _mouseFPS = newFPS;
}

uint MouseController::getFPS()
{
    return _mouseFPS;
}

void MouseController::changeJitter(const int &newJitterVal)
{
    _jitterValue = newJitterVal;
}

int MouseController::getJitterVal()
{
    return _jitterValue;
}

void MouseController::changeSpeed(const double &newMaxSpeedVal, const double &newMinSpeedVal)
{
    _maxSpeed = newMaxSpeedVal;
    _minSpeed = newMinSpeedVal;
}

double MouseController::measureDistance(const QPoint &pA, const QPoint &pB)
{
    return sqrt( pow((pB.x() - pA.x()), 2) + pow((pB.y() - pA.y()), 2) );
}

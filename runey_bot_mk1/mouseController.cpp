#include "mouseController.h"

extern "C"
{
#include "xdo.h"
}

MouseController MouseController::mc = MouseController( SCREEN );
static xdo_t *xDoTool;

MouseController::MouseController( int screen ) :
    _jitterValue( MOUSE_JITTER ),
    _mouseFPS( MOUSE_FPS ),
    _minSpeed( MOUSE_SPEED_MIN ),
    _maxSpeed( MOUSE_SPEED_MAX ),
    _minDelay( MOUSE_DELAY_MIN ),
    _maxDelay( MOUSE_DELAY_MAX ),
    _minCurves( MOUSE_CURVES_MIN ),
    _maxCurves( MOUSE_CURVES_MAX ),
    _p0(0, 0),
    _p1(0, 0),
    _p1Goal(0, 0),
    _p2(0, 0),
    _tSpeed( Util::mapCapped( Util::getDistance( _p0, _p2 ), 0, 500, _maxSpeed, _minSpeed) ),
    _screen( screen )
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
//    _jitterValue = Util::genRandDouble( 1, 100 );
//    _curves = Util::genRandDouble( 1, 100 );
}

void MouseController::mouseMoveRelative( QPoint p )
{
    mouseMove( getMousePos() + p );
}

void MouseController::mouseMoveRelative( int relativeX, int relativeY )
{
    mouseMove( getMousePos() + QPoint( relativeX, relativeY ) );
}

void MouseController::mouseMove( QPoint newPoint )
{
    mouseMove( newPoint.x(), newPoint.y() );
}

void MouseController::mouseMove( int newX, int newY )
{
//    changeRandValues();

    _p0 = getMousePos();
    _p2.setX( newX );
    _p2.setY( newY );

    int curves = Util::map( Util::getDistance( _p0, _p2 ), 0, 1000, MOUSE_CURVES_MIN, MOUSE_CURVES_MAX );

    _p1 = Util::genRandQPointOffset( Util::getMidPoint( _p0, _p2 ), curves * 5 );

    _p1Goal = Util::genRandQPointOffset( Util::getMidPoint( _p0, _p2 ), curves * 5 );

    for (_t = 0; _t <= 1; _t += _tSpeed)
    {
        if (_p1.x() < _p1Goal.x())
            _p1.setX(_p1.x() + Util::genRand(_jitterValue));
        else
            _p1.setX(_p1.x() - Util::genRand(_jitterValue));

        if (_p1.y() < _p1Goal.y())
            _p1.setY(_p1.y() + Util::genRand(_jitterValue));
        else
            _p1.setY(_p1.y() - Util::genRand(_jitterValue));

        if ( floor(Util::genRand(1, 30)) == 1 )
        {
            _p1Goal.setX( (_p0.x() + _p2.x()) / 2 + Util::genRand(-curves * 3, curves * 3) );
            _p1Goal.setY( (_p0.y() + _p2.y()) / 2 + Util::genRand(-curves * 3, curves * 3) );
        }

        _tSpeed = ( Util::mapCapped( Util::getDistance( _p0, _p2 ), 0, 1000, _maxSpeed, _minSpeed) );

        if (_tSpeed < 0.003)
            _tSpeed = Util::genRandDouble(_minSpeed, _maxSpeed);

        _t += Util::genRandDouble(_tSpeed, _tSpeed * 1.5);

        if (_t > 1)
            _t = 1;

//        qDebug() << _t;

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

void MouseController::mousePressRelative( MouseState state, QPoint p )
{
    mousePress( state, getMousePos() + p );
}

void MouseController::mousePressRelative( MouseState state, int relativeX, int relativeY )
{
    mousePress( state, getMousePos() + QPoint( relativeX, relativeY ) );
}

void MouseController::mousePress( MouseState state, QPoint newPoint )
{
    mousePress( state, newPoint.x(), newPoint.y() );
}

void MouseController::mousePress( MouseState state, int newX, int newY)
{
//    if( totalClicks > 30 )
//        return;
    mouseMove(newX, newY);

    if (state == MouseState::Left)
    {
        xdo_mouse_down(xDoTool, CURRENTWINDOW, Button1);
        Sleeper::msleep( static_cast<uint>(Util::genRand( _minDelay, _maxDelay ) ) );
        xdo_mouse_up(xDoTool, CURRENTWINDOW, Button1);
    }
    else if (state == MouseState::Right)
    {
        xdo_mouse_down(xDoTool, CURRENTWINDOW, Button3);
        Sleeper::msleep( static_cast<uint>(Util::genRand( _minDelay, _maxDelay ) ) );
        xdo_mouse_up(xDoTool, CURRENTWINDOW, Button3);
    }
    else if (state == MouseState::Middle)
    {
        xdo_mouse_down(xDoTool, CURRENTWINDOW, Button2);
        Sleeper::msleep( static_cast<uint>(Util::genRand( _minDelay, _maxDelay ) ) );
        xdo_mouse_up(xDoTool, CURRENTWINDOW, Button2);
    }
    totalClicks++;
}

void MouseController::mouseDragRelative( MouseState state, QPoint p )
{
    mouseDrag( state, getMousePos() + p );
}

void MouseController::mouseDragRelative( MouseState state, int relativeX, int relativeY )
{
    mouseDrag( state, getMousePos() + QPoint( relativeX, relativeY ) );
}

void MouseController::mouseDrag( MouseState state, QPoint newPoint )
{
    mouseDrag( state, newPoint.x(), newPoint.y() );
}

void MouseController::mouseDrag( MouseState state, int newX, int newY )
{
    qDebug() << "Dragging to x:" << newX << " y:" << newY;
    if (state == MouseState::Left)
    {
        xdo_mouse_down(xDoTool, CURRENTWINDOW, Button1);
        Sleeper::msleep( static_cast<uint>(Util::genRand( _minDelay, _maxDelay )) );
    }
    else if (state == MouseState::Right)
    {
        xdo_mouse_down(xDoTool, CURRENTWINDOW, Button3);
        Sleeper::msleep( static_cast<uint>(Util::genRand( _minDelay, _maxDelay )) );
    }
    else if (state == MouseState::Middle)
    {
        xdo_mouse_down(xDoTool, CURRENTWINDOW, Button2);
        Sleeper::msleep( static_cast<uint>(Util::genRand( _minDelay, _maxDelay )) );
    }

    mouseMove(newX, newY);

    if (state == MouseState::Left)
    {
        Sleeper::msleep( static_cast<uint>(Util::genRand( _minDelay, _maxDelay )) );
        xdo_mouse_up(xDoTool, CURRENTWINDOW, Button1);
    }
    else if (state == MouseState::Right)
    {
        Sleeper::msleep( static_cast<uint>(Util::genRand( _minDelay, _maxDelay )) );
        xdo_mouse_up(xDoTool, CURRENTWINDOW, Button3);
    }
    else if (state == MouseState::Middle)
    {
        Sleeper::msleep( static_cast<uint>(Util::genRand( _minDelay, _maxDelay )) );
        xdo_mouse_up(xDoTool, CURRENTWINDOW, Button2);
    }
}

void MouseController::setFPS( uint newFPS )
{
    _mouseFPS = newFPS;
}

uint MouseController::getFPS()
{
    return _mouseFPS;
}

void MouseController::setJitter(int newJitterVal )
{
    _jitterValue = newJitterVal;
}

void MouseController::resetJitter()
{
    _jitterValue = MOUSE_JITTER;
}

int MouseController::getJitterVal()
{
    return _jitterValue;
}

void MouseController::setSpeed( double newMinSpeed, double newMaxSpeed )
{
    if( newMinSpeed > newMaxSpeed )
    {
        _maxSpeed = newMinSpeed;
        _minSpeed = newMaxSpeed;
    }
    else
    {
        _maxSpeed = newMaxSpeed;
        _minSpeed = newMinSpeed;
    }
}

void MouseController::resetSpeed()
{
    _maxSpeed = MOUSE_SPEED_MIN;
    _minSpeed = MOUSE_SPEED_MAX;
}

void MouseController::setClickDelay( double newMinDelay, double newMaxDelay )
{
    if( newMinDelay > newMaxDelay )
    {
        _maxDelay = newMinDelay;
        _minDelay = newMaxDelay;
    }
    else
    {
        _maxDelay = newMaxDelay;
        _minDelay = newMinDelay;
    }
}

void MouseController::resetClickDelay()
{
    _maxDelay = MOUSE_DELAY_MIN;
    _minDelay = MOUSE_DELAY_MAX;
}

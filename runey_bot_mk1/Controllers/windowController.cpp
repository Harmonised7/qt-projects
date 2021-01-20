#include "windowController.h"

extern "C"
{
#include "xdo.h"
}

WindowController WindowController::wc = WindowController();
static xdo_t *xDoTool;

WindowController::WindowController()
{
    xDoTool = xdo_new(nullptr);

    qDebug() << "Initialized Window Controller...";
}

WindowController::~WindowController()
{
    xdo_free( xDoTool );
}

void WindowController::focusWindow( ulong id )
{
    xdo_focus_window( xDoTool, id );
}

void WindowController::minimizeWindow( ulong id )
{
    xdo_minimize_window( xDoTool, id );
}

void WindowController::closeWindow( ulong id )
{
    xdo_close_window( xDoTool, id );
}

void WindowController::killWindow( ulong id )
{
    xdo_kill_window( xDoTool, id );
}

void WindowController::testMethod()
{
}

#include "windowController.h"

extern "C"
{
#include "xdo.h"
}

//WindowController WindowController::wc;
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

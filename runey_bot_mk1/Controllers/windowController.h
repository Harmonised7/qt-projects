#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include <QDebug>

#include "Util/defines.h"

class WindowController
{
public:
    ~WindowController();

    static WindowController wc;

private:
    WindowController();
};

#endif // WINDOWCONTROLLER_H

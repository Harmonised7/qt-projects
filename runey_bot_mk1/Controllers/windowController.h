#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

//QT Includes
#include <QDebug>

//Util Includes
#include "Util/defines.h"

typedef unsigned long ulong;

class WindowController
{
public:
    ~WindowController();

    void focusWindow( ulong );
    void minimizeWindow( ulong );

    void closeWindow( ulong );
    void killWindow( ulong );

    void testMethod();

    static WindowController wc;

private:
    WindowController();
};

#endif // WINDOWCONTROLLER_H

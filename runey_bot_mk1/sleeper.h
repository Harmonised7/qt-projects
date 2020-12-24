#ifndef SLEEPER_H
#define SLEEPER_H

// Qt Native Includes //
#include <QThread>
#include <QDebug>

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs)  {QThread::sleep(secs);}
};

#endif // SLEEPER_H

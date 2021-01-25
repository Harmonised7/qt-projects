#ifndef ANTIBANTASK_H
#define ANTIBANTASK_H

#define RIGHTCLICK_SAFE_DOWN 16
#define RIGHTCLICK_SAFE_HORIZONTAL 6

#include "Tasks/task.h"

enum class AntiBan
{
    Left,
    RightClick,
    TypeRandom,
    RotateScreenMiddle,
    RotateScreenArrow
};

class AntiBanTask : public Task
{
public:
    AntiBanTask( int region = 1, bool doMouse = true, bool doKeyboard = true );

    void execute( BotInfo *info ) override;

    static void doAntiBan( BotInfo *info, bool doMouse = true, bool doKeyboard = true );
    static void doAntiBan( cv::Rect area, bool doMouse = true, bool doKeyboard = true );

private:
    int _region;
    bool _doMouse, _doKeyboard;
};

#endif // ANTIBANTASK_H

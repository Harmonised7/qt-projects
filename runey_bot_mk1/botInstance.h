#ifndef BOTINSTANCE_H
#define BOTINSTANCE_H

//Qt
#include <QList>

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

//Bot Includes
#include "Modules/module.h"
#include "Conditions/condition.h"
#include "Tasks/task.h"
#include "Conditions/tabCondition.h"

//Other Includes
#include "defines.h"
#include "mouseController.h"
#include "util.h"
#include "botinfo.h"

class BotInstance
{
public:
    BotInstance( const int &x, const int &y );

    ~BotInstance();

    //Methods
    void addModule( Module *module, bool initModule = false );
    void addImage( int id, cv::Mat image );
    void addColorItem( char color, int item );
    void runModules( QList<Module *> modules );

    cv::Mat handleFrame( const cv::Mat &screen );
private:
    //Objects
    QList<Module *> _initModules;
    QList<Module *> _modules;
    BotInfo *_info;
    bool _init = false;
};

#endif // BOTINSTANCE_H

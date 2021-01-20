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

//Controllers
#include "Controllers/mouseController.h"

//Util Includes
#include "Util/defines.h"
#include "Util/util.h"
#include "Util/timer.h"

//Other Includes
#include "botinfo.h"

enum class ModuleType
{
    Init,
    Ingame,
    Login,
    Background
};

class BotInstance
{
public:
    BotInstance( int x, int y, StrPair loginInfo );

    ~BotInstance();

    //Methods
    void addModule( Module *module, ModuleType type = ModuleType::Ingame );
    void addImage( int id, cv::Mat image );
    void addColorItem( char color, int item );
    void runModules( QList<Module *> modules );

    cv::Mat handleFrame( const cv::Mat &screen );
    StrPair loginInfo;
    BotInfo *info;
private:
    //Objects
    QMap<ModuleType, QList<Module *>> _modules;
    bool _init = false;
};

#endif // BOTINSTANCE_H

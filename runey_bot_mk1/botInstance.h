#ifndef BOTINSTANCE_H
#define BOTINSTANCE_H

#define RS_WIDTH 765
#define RS_HEIGHT 503

#define BAR_WIDTH 72
#define BAR_HEIGHT 34

#define BORDER_HEIGHT 29
#define BORDER_SIZE 4

#define INV_X 558
#define INV_Y 211

#define INV_SLOT_X 42
#define INV_SLOT_Y 36

//Qt
#include <QList>

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

//Other Includes
#include "rndController.h"
#include "mouseController.h"
#include "util.h"
#include "botinfo.h"
#include "condition.h"

class BotInstance
{
public:
    BotInstance();
    BotInstance( const int &x, const int &y );

    ~BotInstance();

    //Methods
    BotInstance *addCondition( Condition *condition );

    QPixmap handleFrame( const cv::Mat &screen );
private:
    //Objects
    RndController _randomNumbers;

    QList<Condition *> _conditions;
    BotInfo *_info;

    //Methods
    void updateInventory();
};

#endif // BOTINSTANCE_H

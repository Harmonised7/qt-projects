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

//Mouse Controller
#define MOUSE_JITTER    5
#define MOUSE_FPS       120
#define MOUSE_MIN       0.015
#define MOUSE_MAX       0.035
#define MOUSE_CURVES    2
#define MOUSE_SCREEN    0

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
    static cv::Rect getInvSlotRect( int index );
    static int getInvSlotIndex( const cv::Rect &rect );
    static int getInvSlotIndex( const QPoint &point );

    void addCondition( Condition *condition );

    QPixmap handleFrame( const cv::Mat &screen );

    void dropItems();

private:
    //Objects
    RndController _randomNumbers;
    static MouseController _mc;

    BotInfo *_info;
    QList<Condition *> _conditions;

    //Methods
    void updateInventory();
};

#endif // BOTINSTANCE_H

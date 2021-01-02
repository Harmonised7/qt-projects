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

//Qt Stuff
#include <QMap>

//Mouse Controller
#define MOUSE_JITTER    5
#define MOUSE_FPS       90
#define MOUSE_MIN       0.015
#define MOUSE_MAX       0.035
#define MOUSE_CURVES    2
#define MOUSE_SCREEN    0

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

//Other Includes
#include "rndcontroller.h"
#include "mouseController.h"
#include "util.h"

class BotInstance
{
public:
    BotInstance();
    BotInstance( const int &x, const int &y );

    //Methods
    QPixmap handleFrame( cv::Mat );
    static cv::Rect getInvSlotRect( int index );

    //Objects n stuff
    int matches;

private:
    //Objects n stuff
    cv::Mat _rsMat;
    cv::Mat _invMat;

    int _x, _y;

    RndController *_randomNumbers;
    static MouseController _mc;

    QMap<int, int> invItems;

    //Methods
    void updateInventory();
};

#endif // BOTINSTANCE_H

#ifndef BOTINFO_H
#define BOTINFO_H

//Qt
#include <QMap>
#include <QList>
#include <QDebug>
#include <QElapsedTimer>

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

//Util Includes
#include "Util/defines.h"
#include "Util/util.h"
#include "Util/timer.h"

enum class BotState
{
    Gather,
    Login,
    Pause,
    Run
};

class BotInfo
{
public: 
    ~BotInfo();
    BotInfo();

    static DropPatterns _dropPatterns;

    cv::Mat rsMat;
    cv::Mat gameMat;
    cv::Mat invMat;

    int x, y;
    QSet<QPoint *> rsFloodMatches;

    //Methods
    QPoint tl(){ return QPoint( x, y ); };
    QPoint br(){ return QPoint( x + RUNELITE_WIDTH, y + RUNELITE_HEIGHT ); };
    void addImage( const int &id, const cv::Mat image );
    QMap<int, cv::Mat> getImages();
    static void updateFlood( cv::Mat inputMat, QSet<QPoint *> *floodMatches );
    static void updateInventory( BotInfo *info );

    //Objects
    Inventory *invItems;
    QMap<char, int> *colorItems;
    Timer *timer;
    Timer *pauseTimer;
    QMap<BotState, bool> states;
    int invTabId = 4, botTabId = 1;

    unsigned long pauseLength = 300000, pauseCount = 0;

private:
    //Objects
    QMap<int, cv::Mat> _images;
};

#endif // BOTINFO_H

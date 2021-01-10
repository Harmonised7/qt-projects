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

//Other Includes
#include "defines.h"
#include "util.h"

enum class BotStates
{
    Gather,
    Login,
    Pause
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
    QElapsedTimer *timer;
    QMap<BotStates, bool> states;
    int tabId = 4;

private:
    //Objects
    QMap<int, cv::Mat> _images;
};

#endif // BOTINFO_H

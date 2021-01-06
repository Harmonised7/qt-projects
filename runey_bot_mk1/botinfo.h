#ifndef BOTINFO_H
#define BOTINFO_H

//Qt
#include <QMap>
#include <QList>
#include <QDebug>

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

//typeDefs
typedef QList<QList<int>> DropPatterns;
typedef QMap<int, int> Inventory;

class BotInfo
{
public: 
    ~BotInfo();
    BotInfo();

    cv::Mat rsMat;
    cv::Mat invMat;

    int x, y;

    Inventory *getItems()
    {
        return &_invItems;
    }

    static DropPatterns _dropPatterns;

private:
    //Objects
    Inventory _invItems;
};

#endif // BOTINFO_H

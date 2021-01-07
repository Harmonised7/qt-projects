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

    static DropPatterns _dropPatterns;

    cv::Mat rsMat;
    cv::Mat invMat;
    cv::Mat floodMat;

    int x, y;

    //Methods
    Inventory *getItems()
    {
        return _invItems;
    }
    void addImage( const int &id, const cv::Mat image );
    QMap<int, cv::Mat> getImages();

private:
    //Objects
    Inventory *_invItems;
    QMap<int, cv::Mat> _images;
};

#endif // BOTINFO_H

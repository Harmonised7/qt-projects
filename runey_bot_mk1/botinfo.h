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

    int x, y;
    QSet<QPoint *> rsFloodMatches;

    //Methods
    QPoint tl()
    {
        return QPoint( x, y );
    }
    void addImage( const int &id, const cv::Mat image );
    QMap<int, cv::Mat> getImages();
    QElapsedTimer *timer;
    bool wcState;
    bool miningState;

    Inventory *invItems;
    QMap<char, int> *colorItems;

private:
    //Objects
    QMap<int, cv::Mat> _images;
};

#endif // BOTINFO_H

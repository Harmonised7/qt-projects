#ifndef UTIL_H
#define UTIL_H

#include <QPoint>

//Qt Stuff
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <qmath.h>
#include <QRandomGenerator>
#include <QDateTime>

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

#include "defines.h"

typedef QPair<cv::Mat, double> MatDoublePair;
typedef QList<QList<int>> DropPatterns;
typedef QPair<int, int> IntPair;
typedef QMap<int, int> Inventory;
typedef QMap<int, IntPair> RangedInventory;
typedef QPair<std::string, std::string> StrPair;

class Util
{
public:
    //Method Declarations
    static QPoint getMidPoint( cv::Rect area );
    static QPoint getMidPoint( QPoint p1, QPoint p2 );

    static int makeAbsolute( int value );

    static QPixmap matToPixmap(const cv::Mat &openCVMat);
    static cv::Mat pixMapToMat(const QPixmap &QtPixmap);
    static QImage pixmapToQImage(const QPixmap &QtPixmap);

    static cv::Point QPointToPoint( QPoint point );
    static QPoint PointToQPoint( cv::Point point );

    static cv::Rect RectFromTwoQPoints( QPoint p1, QPoint p2 );

    static double map(const double &x, const double &in_min, const double &in_max, const double &out_min, const double &out_max);
    static double mapCapped(const double &x, const double &in_min, const double &in_max, const double &out_min, const double &out_max);
    static double cap( const double &x, const double &min_bound, const double &max_bound );

    static cv::Rect getInvTabRect( int index );
    static cv::Rect getBotTabRect( int index );
    static cv::Rect getInvSlotRect( int index );

    static int getInvSlotIndex( const cv::Rect &rect );
    static int getInvSlotIndex( const QPoint &point );

    static double getDistance( QPoint &p1, QPoint &p2 );
    static double getDistance( cv::Point &p1, cv::Point &p2 );

    static int genRand( int bound1, int bound2 = 0 );
    static double genRandDouble( double bound1, double bound2 = 0 );

    static QPoint genRandQPoint( cv::Rect area );
    static QPoint genRandQPoint( cv::Mat mat );
    static QPoint genRandQPoint( QPoint p1, QPoint p2 );
    static QPoint genRandQPointOffset( QPoint p, int offset );
    static QPoint moveQPoint( QPoint p, int moveX, int moveY );

    static cv::Point genRandPoint( cv::Rect area );
    static cv::Point genRandPoint( cv::Mat mat );
    static cv::Point genRandPoint( cv::Point p1, cv::Point p2 );
    static cv::Point genRandPointOffset( cv::Point p, int offset );
    static cv::Point movePoint( cv::Point p, int moveX, int moveY );

    static QList<cv::Rect> findMatches( cv::Mat imageMat, cv::Mat targetMat, double threshold = 0.9 );

    static cv::Rect resizeRect( cv::Rect rect, int shrink );
    static cv::Rect resizeRect( cv::Rect rect, int shrinkX, int shrinkY );

    static bool pixelInRange( cv::Vec3b reference, cv::Vec3b target );
    static bool pixelInRange( cv::Vec3b reference, cv::Vec3b p1, cv::Vec3b p2 );

    static qint64 getEpochMS();

    static double min( double a, double b );
    static double max( double a, double b );
};

#endif // UTIL_H

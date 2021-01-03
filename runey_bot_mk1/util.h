#ifndef UTIL_H
#define UTIL_H

#include <QPoint>

//Qt Stuff
#include "QImage"
#include "QPixmap"

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

class Util
{
public:
    Util();

    //Function Declarations
    static QPoint getMidPoint( cv::Rect area );
    static QPoint getMidPoint( QPoint p1, QPoint p2 );
    static int makeAbsolute( int value );
    static QPixmap matToPixmap(const cv::Mat &openCVMat);
    static cv::Mat pixMapToMat(const QPixmap &QtPixmap);
    static QImage pixmapToQImage(const QPixmap &QtPixmap);
    static cv::Point QPointToPoint( QPoint point );
    static double map(const double &x, const double &in_min, const double &in_max, const double &out_min, const double &out_max);
    static double mapCapped(const double &x, const double &in_min, const double &in_max, const double &out_min, const double &out_max);
    static double cap( const double &x, const double &min_bound, const double &max_bound );
};

#endif // UTIL_H

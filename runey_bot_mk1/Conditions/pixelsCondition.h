#ifndef PIXELSCONDITION_H
#define PIXELSCONDITION_H

//OpenCV Includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

//Other includes
#include "Conditions/condition.h"

class PixelsCondition : public Condition
{
public:
    PixelsCondition( cv::Rect area, cv::Vec3b p1, cv::Vec3b p2 );
    PixelsCondition( cv::Rect area, cv::Vec3b p );

    PixelsCondition( cv::Point pixel, cv::Vec3b p1, cv::Vec3b p2 );
    PixelsCondition( cv::Point pixel, cv::Vec3b p );

    bool checkCondition( BotInfo *info );

private:
    cv::Rect _area;
    cv::Vec3b _p1, _p2;
};

#endif // PIXELSCONDITION_H

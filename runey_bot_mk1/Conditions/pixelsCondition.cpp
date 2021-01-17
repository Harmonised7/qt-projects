#include "pixelsCondition.h"

using namespace cv;

PixelsCondition::PixelsCondition( cv::Rect area, cv::Vec3b p1, cv::Vec3b p2 ) :
    _area( area ),
    _p1( p1 ),
    _p2( p2 )
{
}

PixelsCondition::PixelsCondition( cv::Rect area, cv::Vec3b p ) :
    _area( area ),
    _p1( p ),
    _p2( p )
{
}

PixelsCondition::PixelsCondition( cv::Point pixel, cv::Vec3b p1, cv::Vec3b p2 ) :
    _area( pixel.x, pixel.y, 1, 1 ),
    _p1( p1 ),
    _p2( p2 )
{
}

PixelsCondition::PixelsCondition( cv::Point pixel, cv::Vec3b p ) :
    _area( pixel.x, pixel.y, 1, 1 ),
    _p1( p ),
    _p2( p )
{
}

bool PixelsCondition::checkCondition( BotInfo *info )
{
    Mat test = info->rsMat.clone();
    rectangle( test, _area, Scalar( 255, 255, 255 ) );
    imshow( "pixelCondition", test );
    Vec3b pixel;
    int lowerBound, upperBound;
    for( int i = 0; i < _area.height; i++ )
    {
        for ( int j = 0; j < _area.width; j++ )
        {
            pixel = info->rsMat.at<Vec3b>( _area.y + i, _area.x + j );
            qDebug() << "Blue:" << pixel[0] << "Green:" << pixel[1] << "Red:" << pixel[2];

            bool passed = true;
            for( int c = 0; c < 3; c++ )
            {
                lowerBound = _p1[c];
                upperBound = _p2[c];
                if( lowerBound > upperBound )
                {
                    int temp = lowerBound;
                    lowerBound = upperBound;
                    upperBound = temp;
                }
                if( pixel[c] < lowerBound || pixel[c] > upperBound )
                    passed = false;
            }
            qDebug() << ( passed ? "passed" : "not passed" );
            if( passed )
                return true;
        }
    }
    return false;
}

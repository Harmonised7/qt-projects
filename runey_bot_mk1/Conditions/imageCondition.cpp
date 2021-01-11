#include "imageCondition.h"

using namespace cv;

ImageCondition::ImageCondition( Mat mat, double threshold ) :
    _crop( Rect( 0, 0, RUNELITE_WIDTH, RUNELITE_HEIGHT ) )
{
    _mats.push_back( MatDoublePair( mat, threshold ) );
}

ImageCondition::ImageCondition( QList<MatDoublePair> mats ) :
    _mats( mats )
{
}

bool ImageCondition::checkCondition( BotInfo *info )
{
    if( _cropSet && _crop.width == 160 )
    {
        rectangle( info->rsMat, _crop, Scalar( 255, 255, 0 ) );
        imshow( "ImageCondition", info->rsMat );
    }

    for( MatDoublePair matPair : _mats )
    {
        if( Util::findMatches( ( _cropSet ? info->rsMat( _crop ) : info->rsMat ).clone(), matPair.first, matPair.second ).size() > 0 )
            return true;
    }

    return false;
}

void ImageCondition::setCrop( Rect crop )
{
    _crop = crop;
    _cropSet = true;
}

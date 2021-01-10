#include "imageCondition.h"

ImageCondition::ImageCondition( cv::Mat mat, double threshold )
{
    _mats.push_back( MatDoublePair( mat, threshold ) );
}

ImageCondition::ImageCondition( QList<MatDoublePair> mats ) :
    _mats( mats )
{
}

bool ImageCondition::checkCondition( BotInfo *info )
{
    for( MatDoublePair matPair : _mats )
    {
        if( Util::findMatches( info->rsMat.clone(), matPair.first, matPair.second ).size() > 0 )
            return true;
    }

    return false;
}

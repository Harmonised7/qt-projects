#include "clickImagesTask.h"

using namespace cv;

ClickImagesTask::ClickImagesTask( Mat mat, double threshold )
{
    mat = mat.clone();
    _mats.push_back( MatDoublePair( mat, threshold ) );
}

ClickImagesTask::ClickImagesTask( QList<Mat> mats )
{
    for( Mat mat : mats )
    {
        mat = mat.clone();
        _mats.push_back( MatDoublePair( mat, DEFAULT_THRESHOLD ) );
    }
}

ClickImagesTask::ClickImagesTask( QList<MatDoublePair> mats )
{
    _mats += mats;
}

void ClickImagesTask::execute( BotInfo *info )
{
    QList<Rect> matches;

    for( MatDoublePair matPair : _mats )
    {
        matches += Util::findMatches( info->rsMat.clone(), matPair.first, matPair.second );
    }
    for( int i = 0; i < matches.size(); i++ )
    {
        Rect match = matches[ Util::genRand( matches.size()-1 ) ];
        rectangle( info->rsMat, match, Scalar( 255, 255, 255 ) );
        imshow( "potato", info->rsMat );
        MouseController::mc.mousePress( MouseStates::Left, QPoint( info->x, info->y ) + Util::genRandQPoint( match ) );
    }
}

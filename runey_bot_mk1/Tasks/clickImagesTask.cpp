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

void ClickImagesTask::setCrop( Rect crop )
{
    _crop = crop;
    _cropOffset = QPoint( crop.x, crop.y );
    _cropSet = true;
}

void ClickImagesTask::execute( BotInfo *info )
{
    QList<Rect> matches;

//    rectangle( info->rsMat, _crop, Scalar( 255, 255, 255 ) );
//    imshow( "clickImages", info->rsMat );

    for( MatDoublePair matPair : _mats )
    {
        matches += Util::findMatches( ( _cropSet ? info->rsMat( _crop ) : info->rsMat ).clone(), matPair.first, matPair.second );
    }
    for( int i = 0; i < matches.size(); i++ )
    {
        Rect match = matches[ Util::genRand( matches.size()-1 ) ];
//        rectangle( info->rsMat, Rect( match.x + _cropOffset.x(), match.y + _cropOffset.y(), match.width, match.height ), Scalar( 255, 255, 255 ) );
//        imshow( "clickImages found", info->rsMat );
        MouseController::mc.mousePress( MouseState::Left, _cropOffset + info->tl() + Util::genRandQPoint( match ) );
    }
}

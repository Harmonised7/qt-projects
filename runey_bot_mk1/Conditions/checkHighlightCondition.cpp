#include "checkHighlightCondition.h"

using namespace cv;

CheckHighlightCondition::CheckHighlightCondition( bool type, Vec3b pixel ) :
    _type( type ),
    _p1( pixel ),
    _p2( pixel )
{
}

CheckHighlightCondition::CheckHighlightCondition( bool type, Vec3b p1, Vec3b p2 ) :
    _type( type ),
    _p1( p1 ),
    _p2( p2 )
{
}


bool CheckHighlightCondition::checkCondition( BotInfo *info )
{
    BotInfo::updateFlood( info->gameMat( Rect( Point( 4, 4 ), Point( info->gameMat.cols, info->gameMat.rows ) ) ), &info->rsFloodMatches, _p1, _p2 );
    return info->rsFloodMatches.size() > 0 == _type;
}

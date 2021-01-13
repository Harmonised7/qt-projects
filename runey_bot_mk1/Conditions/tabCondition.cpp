#include "tabCondition.h"

using namespace cv;

TabCondition::TabCondition( int tab, bool boolType ) :
    _tab( tab ),
    _boolType( boolType )
{
}

bool TabCondition::checkCondition( BotInfo *info )
{
    info->invTabId = getCurrentTab( info );
    if( _boolType )
        return info->invTabId == _tab;
    else
        return info->invTabId != _tab;
}

int TabCondition::getCurrentTab( BotInfo *info )
{
    Rect tabRect;
    int tab = 0;
    Vec3b pixel;

    for( int i = 1; i <= 14; i++ )
    {
        tabRect = Util::getInvTabRect( i );
        for( int j = 5; j < INV_TAB_WIDTH - 5; j++ )
        {
//            info->rsMat.at<Vec3b>( tabRect.y, tabRect.x + j ) = Vec3b( 255, 255, 255 );
            pixel = info->rsMat.at<Vec3b>( tabRect.y, tabRect.x + j );
            if( pixel[2] > 90 && pixel[1] < 50 && pixel[0] < 50 )
            {
//                qDebug() << "current tab:" << i;
                return i;
            }
        }
    }

//    if( tab == 0 )
//        qDebug() << "Could not find current tab!";
    return tab;
}

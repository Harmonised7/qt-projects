#include "Tasks/useItemsTask.h"

UseItemsTask::UseItemsTask( const int &item1, const int &item2, const int &times ) :
    _item1( item1 ),
    _item2( item2 ),
    _times( times )
{

}

void UseItemsTask::execute( BotInfo *info )
{
    Inventory *items = info->getItems();
    QList<int> *itemsGroup1 = new QList<int>();
    QList<int> *itemsGroup2 = new QList<int>();
    int item, availableTimes;

    for( int slot : items->keys() )
    {
        item = items->value( slot );

        if( item == _item1 )
            itemsGroup1->push_back( slot );
        else if( item == _item2 )
            itemsGroup2->push_back( slot );
    }

    availableTimes = cv::min( itemsGroup1->size(), itemsGroup2->size() );

    MouseController::_mc.mousePress( MouseStates::Left, RndController::genRandPoint( Util::getInvSlotRect( i ) ) + QPoint( info->x, info->y ), 50, 75 );
}

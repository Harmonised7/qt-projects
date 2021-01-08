#include "Tasks/useItemsTask.h"

UseItemsTask::UseItemsTask( const int &item1, const int &item2, const int &times ) :
    _item1( item1 ),
    _item2( item2 ),
    _times( times )
{

}

void UseItemsTask::execute( BotInfo *info )
{
    Inventory *items = info->invItems;
    QList<int> *itemsGroup1 = new QList<int>();
    QList<int> *itemsGroup2 = new QList<int>();
    int item, times, slot1, slot2;


    for( int slot : items->keys() )
    {
        item = items->value( slot );

        if( item == _item1 )
            itemsGroup1->push_back( slot );
        else if( item == _item2 )
            itemsGroup2->push_back( slot );
    }

    if( itemsGroup1->size() > itemsGroup2->size() )
    {
        QList<int> *temp = itemsGroup1;
        itemsGroup2 = itemsGroup1;
        itemsGroup1 = temp;
    }

    times = cv::min( _times, itemsGroup1->size() );

    for( int i = 0; i < times; i++ )
    {
        slot1 = itemsGroup1->value( Util::genRand( itemsGroup1->size() - 1 ) );
    }

//    MouseController::_mc.mousePress( MouseStates::Left, RndController::genRandPoint( Util::getInvSlotRect( i ) ) + QPoint( info->x, info->y ), 50, 75 );
}

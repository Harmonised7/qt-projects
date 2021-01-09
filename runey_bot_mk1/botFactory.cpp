#include "botFactory.h"

BotInstance *BotFactory::makeGathererBot( int botX, int botY )
{
//    cv::Mat logs = Util::pixMapToMat( QPixmap( ":/icons/Images/Logs.png" ) );

    BotInstance *bot = new BotInstance( botX, botY );
    QList<Condition *> conditions;
    QList<Task *> tasks;

    //Init Modules

    //Make sure inv tab
    bot->addModule( new Module( new TabCondition( 4, false ), new ChangeTabTask( 4 ) ) );

    //Drop items
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    ClickItemsTask *clickItemsTask = new ClickItemsTask( 9001, 5, 26 );
    clickItemsTask->setFailRate( Util::genRand( 5, 15 ) );

    conditions.push_back( new InventoryCondition( 9001, true, 10, 20 ) );
    tasks.push_back( clickItemsTask );

    bot->addModule( new Module( conditions, tasks ) );

    //Antiban - Check random tab
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    conditions.push_back( new TimeoutCondition( 30000, 90000 ) );
    tasks.push_back( new ChangeTabTask( IntPair( 1, 7 ) ) );
    tasks.push_back( new AntiBanTask( 2 ) );

    bot->addModule( new Module( conditions, tasks ) );

    //Click Highlights
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    conditions.push_back( new TimeoutCondition( 2000, 5000 ) );
    conditions.push_back( new StateCondition( 1 ) );
    tasks.push_back( new ClickHighlightTask() );
//    tasks.push_back( randomChangeTabTask );

    bot->addModule( new Module( conditions, tasks ) );

    bot->addColorItem( 'b', 9001 );

    return bot;
}

#include "botFactory.h"

BotInstance *BotFactory::makeWcBot( int botX, int botY )
{
//    cv::Mat logs = Util::pixMapToMat( QPixmap( ":/icons/Images/Logs.png" ) );

    TimeoutCondition *timeoutCondition = new TimeoutCondition( 2000, 5000 );
    StateCondition *stateCondition = new StateCondition( 1 );
    InventoryCondition *fullInvCondition = new InventoryCondition( 9001, true, 20 );
    ClickItemsTask *clickItemsTask = new ClickItemsTask( 9001, 5, 26 );
    ClickHighlightTask *clickHighlistTask = new ClickHighlightTask();
    AntiBanTask *antiBanTask = new AntiBanTask();

    BotInstance *bot = new BotInstance( botX, botY );
    QList<Condition *> conditions = QList<Condition *>();
    QList<Task *> tasks = QList<Task *>();

    //Click Highlights
    conditions.push_back( timeoutCondition );
    conditions.push_back( stateCondition );
    tasks.push_back( clickHighlistTask );

    bot->addModule( new Module( conditions, tasks ) );

    //Drop items
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    conditions.push_back( fullInvCondition );
    tasks.push_back( clickItemsTask );
    tasks.push_back( clickHighlistTask );

    bot->addModule( new Module( conditions, tasks ) );

    //AntiBan
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    timeoutCondition = new TimeoutCondition( 5000, 45000 );

    conditions.push_back( timeoutCondition );
    tasks.push_back( antiBanTask );

    bot->addModule( new Module( conditions, tasks ) );

    bot->addColorItem( 'b', 9001 );

    return bot;
}

BotInstance *BotFactory::makeMiningBot( int botX, int botY )
{
//    cv::Mat copperOre = Util::pixMapToMat( QPixmap( ":/icons/Images/Copper_ore.png" ) );

    TimeoutCondition *timeoutCondition = new TimeoutCondition( 2000, 5000 );
    StateCondition *stateCondition = new StateCondition( 2 );
    InventoryCondition *fullInvCondition = new InventoryCondition( 9001, true, 20 );
    ClickItemsTask *clickItemsTask = new ClickItemsTask( 9001, 5, 26 );
    ClickHighlightTask *clickHighlistTask = new ClickHighlightTask();
    AntiBanTask *antiBanTask = new AntiBanTask();

    BotInstance *bot = new BotInstance( botX, botY );
    QList<Condition *> conditions = QList<Condition *>();
    QList<Task *> tasks = QList<Task *>();

    //Click Highlights
    conditions.push_back( timeoutCondition );
    conditions.push_back( stateCondition );
    tasks.push_back( clickHighlistTask );

    bot->addModule( new Module( conditions, tasks ) );

    //Drop items
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    conditions.push_back( fullInvCondition );
    tasks.push_back( clickItemsTask );
    tasks.push_back( clickHighlistTask );

    bot->addModule( new Module( conditions, tasks ) );

    //AntiBan
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    timeoutCondition = new TimeoutCondition( 5000, 45000 );

    conditions.push_back( timeoutCondition );
    tasks.push_back( antiBanTask );

    bot->addModule( new Module( conditions, tasks ) );

    bot->addColorItem( 'b', 9001 );

    return bot;
}

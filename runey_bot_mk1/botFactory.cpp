#include "botFactory.h"

using namespace cv;

BotInstance *BotFactory::makeGathererBot( int botX, int botY, StrPair loginInfo )
{
    BotInstance *bot = new BotInstance( botX, botY, loginInfo );
    addLoginModules( bot );
    addGathererModules( bot );
    return bot;
}

void BotFactory::addGathererModules( BotInstance *bot )
{
//    cv::Mat logs = Util::pixMapToMat( QPixmap( ":/icons/Images/Logs.png" ) );

    QList<Condition *> conditions;
    QList<Task *> tasks;

    //Drop items
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    ClickItemsTask *clickItemsTask = new ClickItemsTask( 9001, 5, 26 );
    clickItemsTask->setFailRate( Util::genRand( 5, 15 ) );
    tasks = QList<Task *>();

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
    conditions.push_back( new StateCondition( BotStates::Gather ) );
    tasks.push_back( new ClickHighlightTask() );
//    tasks.push_back( randomChangeTabTask );

    bot->addModule( new Module( conditions, tasks ) );

    bot->addColorItem( 'b', 9001 );
}

void BotFactory::addLoginModules( BotInstance *bot )
{
    cv::Mat existingUser = Util::pixMapToMat( QPixmap( ":/icons/Images/Existing_user.png" ) );
    cv::Mat clickHereToPlay = Util::pixMapToMat( QPixmap( ":/icons/Images/Click_here_to_play.png" ) );
    cv::Mat login = Util::pixMapToMat( QPixmap( ":/icons/Images/Login.png" ) );
    cv::Mat ok = Util::pixMapToMat( QPixmap( ":/icons/Images/Ok.png" ) );

    QList<MatDoublePair> notLoggedInMats;
    QList<MatDoublePair> clickMats;
    QList<Condition *> conditions;
    QList<Task *> tasks;
    QList<Task *> elseTasks;

    //Set login state Module
    conditions = QList<Condition *>();
    tasks = QList<Task *>();
    elseTasks = QList<Task *>();

    notLoggedInMats.push_back( MatDoublePair( existingUser, DEFAULT_THRESHOLD ) );
    notLoggedInMats.push_back( MatDoublePair( clickHereToPlay, DEFAULT_THRESHOLD ) );
    notLoggedInMats.push_back( MatDoublePair( login, 200 ) );
    notLoggedInMats.push_back( MatDoublePair( ok, 200 ) );

    conditions.push_back( new ImageCondition( notLoggedInMats ) );
    tasks.push_back( new SetStateTask( BotStates::Login, false ) );
    elseTasks.push_back( new SetStateTask( BotStates::Login, true ) );

    bot->addModule( new Module( conditions, tasks ) );

    //Find Login Screen Module
    clickMats = QList<MatDoublePair>();
    clickMats.push_back( MatDoublePair( ok, 200 ) );
    clickMats.push_back( MatDoublePair( existingUser, DEFAULT_THRESHOLD ) );
    clickMats.push_back( MatDoublePair( clickHereToPlay, DEFAULT_THRESHOLD ) );

    bot->addModule( new Module( new ClickImagesTask( clickMats ) ) );

    //Login Module
    conditions.push_back( new ImageCondition( login, 200 ) );
    Rect focusArea = Rect( bot->info->x + FOCUS_CLICK_SHRINK, bot->info->y + FOCUS_CLICK_SHRINK, RUNELITE_WIDTH - FOCUS_CLICK_SHRINK*2, RUNELITE_HEIGHT - FOCUS_CLICK_SHRINK*2 );
    tasks.push_back( new ClickAreaTask( MouseStates::Left, focusArea ) );
    tasks.push_back( new KeyboardTask( KeyboardStates::Press, "Escape" ) );
    tasks.push_back( new KeyboardTask( KeyboardStates::Press, "Return" ) );
    tasks.push_back( new KeyboardTask( KeyboardStates::Write, bot->loginInfo.first ) );
    tasks.push_back( new KeyboardTask( KeyboardStates::Press, "Tab" ) );
    tasks.push_back( new KeyboardTask( KeyboardStates::Write, bot->loginInfo.second ) );
    tasks.push_back( new KeyboardTask( KeyboardStates::Press, "Return" ) );

    bot->addModule( new Module( conditions, tasks ) );
}

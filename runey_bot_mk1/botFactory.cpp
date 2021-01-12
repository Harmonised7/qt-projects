#include "botFactory.h"

using namespace cv;

BotInstance *BotFactory::makeGathererBot( int botX, int botY, StrPair loginInfo )
{
    BotInstance *bot = new BotInstance( botX, botY, loginInfo );
    addLoginModules( bot );
    addRunOnModules( bot );
    addGathererModules( bot );
    addPauseModules( bot );
    return bot;
}

void BotFactory::addGathererModules( BotInstance *bot )
{
//    cv::Mat logs = Util::pixMapToMat( QPixmap( ":/icons/Images/Logs.png" ) );

    QList<Condition *> conditions;
    QList<Task *> tasks;

    //Make sure inv
    bot->addModule( new Module( new TabCondition( 4, false ), new ChangeTabTask( 4 ) ) );

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
    conditions.push_back( new StateCondition( BotState::Gather, false ) );
    tasks.push_back( new ClickHighlightTask() );
//    tasks.push_back( randomChangeTabTask );

    bot->addModule( new Module( conditions, tasks ) );

    bot->addColorItem( 'b', 9001 );
}

void BotFactory::addLoginModules( BotInstance *bot )
{
    Mat existingUser = Util::pixMapToMat( QPixmap( ":/icons/Images/Existing_user.png" ) );
    Mat welcomeMessage = Util::pixMapToMat( QPixmap( ":/icons/Images/Welcome_message.png" ) );
    Mat login = Util::pixMapToMat( QPixmap( ":/icons/Images/Login.png" ) );
    Mat cancel = Util::pixMapToMat( QPixmap( ":/icons/Images/Cancel.png" ) );
    Mat ok = Util::pixMapToMat( QPixmap( ":/icons/Images/Ok.png" ) );
    Mat wiki = Util::pixMapToMat( QPixmap( ":/icons/Images/Wiki.png" ) );
    Mat tryAgain = Util::pixMapToMat( QPixmap( ":/icons/Images/Try_again.png" ) );

    QList<MatDoublePair> clickMats;
    QList<Condition *> conditions;
    QList<Task *> tasks;
    QList<Task *> elseTasks;

    //Set login state Module
    conditions = QList<Condition *>();
    tasks = QList<Task *>();
    elseTasks = QList<Task *>();

    Rect playButtonArea = Util::resizeRect( Rect( Point( PLAY_BUTTON_X1, PLAY_BUTTON_Y1 + 80 ), Point( PLAY_BUTTON_X2, PLAY_BUTTON_Y2 ) ), -5 );
    Rect welcomeMessageArea = Util::resizeRect( Rect( WELCOME_MESSAGE_X, WELCOME_MESSAGE_Y, WELCOME_MESSAGE_WIDTH, WELCOME_MESSAGE_HEIGHT ), 5 );
    Rect buttonsArea = Rect( Point( LOGIN_BUTTONS_X1, LOGIN_BUTTONS_Y1 ), Point( LOGIN_BUTTONS_X2, LOGIN_BUTTONS_Y2 ) );
    Rect wikiArea = Rect( Point( WIKI_X1, WIKI_Y1 ), Point( WIKI_X2, WIKI_Y2 ) );

    ImageCondition *imageCondition;
    imageCondition = new ImageCondition( wiki, DEFAULT_THRESHOLD );
    imageCondition->setCrop( Util::resizeRect( Util::resizeRect( wikiArea, 5 ), 5 ) );
    conditions.push_back( imageCondition );

    tasks.push_back( new SetStateTask( BotState::Login, false ) );
    elseTasks.push_back( new SetStateTask( BotState::Login, true ) );

    Module *loginStateModule = new Module( conditions, tasks, elseTasks );
    loginStateModule->setMatchReq( 1 );

    bot->addModule( loginStateModule, ModuleType::Background );

    //Find Login Screen Module
    clickMats = QList<MatDoublePair>();
    clickMats.push_back( MatDoublePair( ok, 200 ) );
    clickMats.push_back( MatDoublePair( tryAgain, 200 ) );
    clickMats.push_back( MatDoublePair( existingUser, DEFAULT_THRESHOLD ) );

    ClickImagesTask *clickLoginButtons = new ClickImagesTask( clickMats );
    clickLoginButtons->setCrop( buttonsArea );

//    Mat test = Mat( buttonsArea.height, buttonsArea.width, CV_8UC3, Scalar( 0 ) );
//    imshow( "test", test );

    bot->addModule( new Module( clickLoginButtons ), ModuleType::Login );

    //Login Module
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    conditions.push_back( new ImageCondition( login, 200 ) );
    Rect focusArea = Rect( Point( PLAY_BUTTON_X1, PLAY_BUTTON_Y1 + 80 ), Point( PLAY_BUTTON_X2, PLAY_BUTTON_Y2 ) );
    tasks.push_back( new ClickAreaTask( MouseState::Right, focusArea ) );
    tasks.push_back( new DelayTask( 1000, 2000 ) );
    tasks.push_back( new KeyboardTask( KeyboardState::Press, "Escape" ) );
    tasks.push_back( new DelayTask( 1000, 2000 ) );
    tasks.push_back( new KeyboardTask( KeyboardState::Press, "Return" ) );
    tasks.push_back( new DelayTask( 1000, 2000 ) );
    tasks.push_back( new KeyboardTask( KeyboardState::Write, bot->loginInfo.first ) );
    tasks.push_back( new KeyboardTask( KeyboardState::Press, "Tab" ) );
    tasks.push_back( new KeyboardTask( KeyboardState::Write, bot->loginInfo.second ) );
    tasks.push_back( new KeyboardTask( KeyboardState::Press, "Return" ) );
    tasks.push_back( new DelayTask( 5000, 10000 ) );

    bot->addModule( new Module( conditions, tasks ), ModuleType::Login );

    //Click play now, hold up arrow key for a while Module
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    ImageCondition *welcomeMessageCondition = new ImageCondition( welcomeMessage );
    welcomeMessageCondition->setCrop( welcomeMessageArea );
    conditions.push_back( welcomeMessageCondition );
    ClickAreaTask *clickPlayButtonTask = new ClickAreaTask( MouseState::Left, Util::resizeRect( playButtonArea, -5 ) );
    tasks.push_back( new KeyboardTask( KeyboardState::Down, "Up" ) );
    tasks.push_back( new DelayTask( 1200, 2300 ) );
    tasks.push_back( new KeyboardTask( KeyboardState::Up, "Up" ) );
    tasks.push_back( clickPlayButtonTask );

    bot->addModule( new Module( conditions, tasks ), ModuleType::Login );
    //
}

void BotFactory::addPauseModules( BotInstance *bot )
{
    QList<Condition *> conditions;
    QList<Task *> tasks;

    conditions.push_back( new TimeoutCondition( 120 * 60 * 1000, 240 * 60 * 1000 ) );
    tasks.push_back( new SetStateTask( BotState::Pause, true ) );
    tasks.push_back( new TimerTask( TimerOperation::Restart ) );

    //Set state to pause
    bot->addModule( new Module( conditions, tasks ) );
//    bot->addModule( new Module( new TimeoutCondition( 15000, 20000 ), new SetStateTask( BotState::Pause, true ) ) );

    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    //If Pause, but still logged in, log out module
    conditions.push_back( new TimeoutCondition( 1000, 3000 ) );
    conditions.push_back( new StateCondition( BotState::Pause, true ) );
    conditions.push_back( new StateCondition( BotState::Login, false ) );
    tasks.push_back( new TakeBreakTask( 20 * 60 * 1000, 60 * 60 * 1000 ) );
    bot->addModule( new Module( conditions, tasks ), ModuleType::Background );
}

void BotFactory::addRunOnModules( BotInstance *bot )
{
    QList<Condition *> conditions;
    QList<Task *> tasks;

    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    conditions.push_back( new TimeoutCondition( 15000, 90000 ) );
    conditions.push_back( new StateCondition( BotState::Run, 0 ) );
    tasks.push_back( new ClickAreaTask( MouseState::Left, Rect( Point( RUN_X1, RUN_Y1 ), Point( RUN_X2, RUN_Y2  ) ) ) );

    bot->addModule( new Module( conditions, tasks ) );
}

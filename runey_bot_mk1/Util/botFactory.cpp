#include "botFactory.h"

using namespace cv;

BotInstance *BotFactory::makeGathererBot( QPoint pos, StrPair loginInfo, bool dropper )
{
    BotInstance *bot = new BotInstance( pos.x(), pos.y(), loginInfo );

    addLoginModules( bot );
    addEssentialModules( bot );
    addRunOnModules( bot );
    addGathererModules( bot, dropper );
    addPauseModules( bot );

//    addDebugModules( bot );

    return bot;
}

BotInstance *BotFactory::makeKillerBot( QPoint pos, StrPair loginInfo )
{
    BotInstance *bot = new BotInstance( pos.x(), pos.y(), loginInfo );
    addLoginModules( bot );
    addEssentialModules( bot );
    addRunOnModules( bot );
    addKillerModules( bot );
    addPauseModules( bot );

//    addDebugModules( bot );

    return bot;
}

void BotFactory::addKillerModules( BotInstance *bot )
{
    QList<Condition *> conditions;
    QList<Task *> tasks;
    QList<Task *> elseTasks;

    conditions.push_back( new PixelsCondition( Rect( ENEMY_HP_BAR_X, ENEMY_HP_BAR_Y, 5, 1 ), Vec3b( 0, 128, 0 ), Vec3b( 75, 255, 75 ) ) );
    tasks.push_back( new SetStateTask( BotState::Combat, true ) );
    elseTasks.push_back( new SetStateTask( BotState::Combat, false ) );
    bot->addModule( new Module( conditions, tasks, elseTasks ) );

    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    conditions.push_back( new TimeoutCondition( 1000, 5000 ) );
    conditions.push_back( new StateCondition( BotState::Combat, false ) );
    tasks.push_back( new SetMouseValuesTask( MouseValueType::Speed, 0.0075, 0.015 ) );
    //Click gate
    tasks.push_back( new ClickHighlightTask( Vec3b( 150, 0, 0 ), Vec3b( 255, 10, 10 ) ) );
    tasks.push_back( new ClickHighlightTask( Vec3b( 0, 150, 0 ), Vec3b( 10, 255, 10 ) ) );
    tasks.push_back( new SetMouseValuesTask( MouseValueType::Speed, MOUSE_SPEED_MIN, MOUSE_SPEED_MAX ) );
    bot->addModule( new Module( conditions, tasks ) );
}

void BotFactory::addEssentialModules( BotInstance *bot )
{
    cv::Mat closeInterfaceX = Util::pixMapToMat( QPixmap( ":/icons/Images/Close_interface_x.png" ) );

    QList<Condition *> conditions;
    QList<Task *> tasks;

    //Exit random interfaces
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    conditions.push_back( new TimeoutCondition( 2000, 5000 ) );
    ClickImagesTask *exitInterfacesTask = new ClickImagesTask( closeInterfaceX, DEFAULT_THRESHOLD );
    exitInterfacesTask->setCrop( Util::resizeRect( Rect( Point( CLOSE_INTERFACE_X1, CLOSE_INTERFACE_Y1 ), Point( CLOSE_INTERFACE_X2, CLOSE_INTERFACE_Y2 ) ), 5 ) );
    tasks.push_back( exitInterfacesTask );

    bot->addModule( new Module( conditions, tasks ) );
}

void BotFactory::addGathererModules( BotInstance *bot, bool dropper )
{
    cv::Mat bankText = Util::pixMapToMat( QPixmap( ":/icons/Images/Bank_text.png" ) );

    QList<Condition *> conditions;
    QList<Task *> tasks;
    QList<Task *> elseTasks;

    //Set Gather State
    conditions = QList<Condition *>();
    tasks = QList<Task *>();
    elseTasks = QList<Task *>();

    conditions.push_back( new PixelsCondition( Rect( GATHER_STATE_X, GATHER_STATE_Y, 50, 1 ), Vec3b( 0, 255, 0 ) ) );
    tasks.push_back( new SetStateTask( BotState::Gather, true ) );
    elseTasks.push_back( new SetStateTask( BotState::Gather, false ) );

    bot->addModule( new Module( conditions, tasks, elseTasks ) );

    //Show Inv chance
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    conditions.push_back( new ChanceCondition( 80, 92 ) );
    conditions.push_back( new TabCondition( 4, false ) );
    tasks.push_back( new ChangeTabTask( 4, TabType::Inventory ) );

    bot->addModule( new Module( conditions, tasks ) );

    //Full Inv

    if( dropper )
    {
        //Drop items
        conditions = QList<Condition *>();
        tasks = QList<Task *>();
        conditions.push_back( new TabCondition( 4, true ) );
        conditions.push_back( new InventoryCondition( 9001, true, 10, 20 ) );
        ClickItemsTask *clickItemsTask = new ClickItemsTask( 9001, 5, 28 );
        clickItemsTask->setFailRate( Util::genRand( 5, 25 ) );
        tasks.push_back( clickItemsTask );
        tasks.push_back( new ClickHighlightTask( Vec3b( 150, 10, 10 ), Vec3b( 255, 0, 0 ) ) );
        bot->addModule( new Module( conditions, tasks ) );
    }
    else
    {
        //Set Inside Bank State
        conditions = QList<Condition *>();
        tasks = QList<Task *>();
        elseTasks = QList<Task *>();
        ImageCondition *bankTextVisibleCondition = new ImageCondition( bankText, 0.2 );
        bankTextVisibleCondition->setCrop( Util::resizeRect( Rect( Point( BANK_TEXT_X1, BANK_TEXT_Y1 ), Point( BANK_TEXT_X2, BANK_TEXT_Y2 ) ), 5 ) );
        conditions.push_back( bankTextVisibleCondition );
        tasks.push_back( new SetStateTask( BotState::InBank, true ) );
        elseTasks.push_back( new SetStateTask( BotState::InBank, false ) );
        bot->addModule( new Module( conditions, tasks, elseTasks ), ModuleType::Background );

        //If Bank Interface Open
        conditions = QList<Condition *>();
        tasks = QList<Task *>();
        conditions.push_back( new StateCondition( BotState::InBank, true ) );
        //Atleast 5 highlighted Items
        conditions.push_back( new InventoryCondition( 9001, true, 5 ) );
        tasks.push_back( new SetStateTask( BotState::Banking, false ) );
        tasks.push_back( new DelayTask( 200, 2000 ) );
        tasks.push_back( new ClickAreaTask( MouseState::Left, Rect( Point( DEPOSIT_ALL_BUTTON_X1, DEPOSIT_ALL_BUTTON_Y1 ), Point( DEPOSIT_ALL_BUTTON_X2, DEPOSIT_ALL_BUTTON_Y2 ) ) ) );
        bot->addModule( new Module( conditions, tasks ), ModuleType::Banking );

        //Set Banking State when inv full
        conditions = QList<Condition *>();
        tasks = QList<Task *>();
        elseTasks = QList<Task *>();
        conditions.push_back( new TabCondition( 4, true ) );
        conditions.push_back( new InventoryCondition( 9001, true, 18, 24 ) );
        tasks.push_back( new SetStateTask( BotState::Banking, true ) );
        bot->addModule( new Module( conditions, tasks, elseTasks ) );

        //If Banking, but bank not open, click bank
        conditions = QList<Condition *>();
        tasks = QList<Task *>();

        conditions.push_back( new TimeoutCondition( 1000, 10000 ) );
        conditions.push_back( new StateCondition( BotState::InBank, false ) );
        tasks.push_back( new ClickHighlightTask( Vec3b( 0, 150, 0 ), Vec3b( 10, 255, 10 ) ) );
        tasks.push_back( new DelayTask( 1000, 3000 ) );
        bot->addModule( new Module( conditions, tasks ), ModuleType::Banking );

        //If Not Banking, but bank is open, exit Bank
        conditions = QList<Condition *>();
        tasks = QList<Task *>();

        conditions.push_back( new TimeoutCondition( 1000, 6000 ) );
        conditions.push_back( new StateCondition( BotState::InBank, true ) );
        tasks.push_back( new ClickAreaTask( MouseState::Left, Rect( Point( EXIT_BANK_BUTTON_X1, EXIT_BANK_BUTTON_Y2 ), Point( EXIT_BANK_BUTTON_X2, EXIT_BANK_BUTTON_Y2 ) ) ) );
        bot->addModule( new Module( conditions, tasks ) );
    }

    //Antiban - Check random inv tab
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    conditions.push_back( new TimeoutCondition( 30000, 150000 ) );
    tasks.push_back( new ChangeTabTask( IntPair( 1, 14 ), TabType::Inventory ) );
    tasks.push_back( new AntiBanTask( 2 ) );

    bot->addModule( new Module( conditions, tasks ) );

    //Antiban - Check random bot tab
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    conditions.push_back( new TimeoutCondition( 300000, 900000 ) );
    tasks.push_back( new ChangeTabTask( IntPair( 1, 6 ), TabType::Bottom ) );

    bot->addModule( new Module( conditions, tasks ) );

    //Click Highlights
    conditions = QList<Condition *>();
    tasks = QList<Task *>();

    conditions.push_back( new TimeoutCondition( 2500, 7500 ) );
    conditions.push_back( new StateCondition( BotState::Gather, false ) );
    tasks.push_back( new ClickHighlightTask( Vec3b( 150, 0, 0 ), Vec3b( 255, 10, 10 ) ) );

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

    conditions.push_back( new TimeoutCondition( 120 * 60 * 1000, 360 * 60 * 1000 ) );
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

    conditions.push_back( new TimeoutCondition( 45000, 180000 ) );
    conditions.push_back( new StateCondition( BotState::Run, 0 ) );
    tasks.push_back( new ClickAreaTask( MouseState::Left, Rect( Point( RUN_X1, RUN_Y1 ), Point( RUN_X2, RUN_Y2  ) ) ) );

    bot->addModule( new Module( conditions, tasks ) );
}

//void BotFactory::addDebugModules( BotInstance *bot )
//{
//    cv::Mat bankText = Util::pixMapToMat( QPixmap( ":/icons/Images/Bank_text.png" ) );

//    QList<Condition *> conditions;
//    QList<Task *> tasks;
//    QList<Task *> elseTasks;


//}

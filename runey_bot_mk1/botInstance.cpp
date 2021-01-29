#include "botInstance.h"

using namespace cv;

BotInstance::BotInstance( int x, int y, StrPair loginInfo ) :
    loginInfo( loginInfo )
{
    info = new BotInfo;
    info->x = x,
    info->y = y;
    info->pauseTimer = new Timer;
    info->timer = new Timer;
    info->timer->start();
}

Mat BotInstance::handleFrame( const cv::Mat &screen )
{
    //Prepare stuff for Modules
    info->releaseMemory();
    info->processScreen();

//    qDebug() << "gather state" << info->states.value( BotState::Gather );

    //Login Modules

    //Draw stuff
//    Rect rect( INV_SLOTS_X, INV_SLOTS_Y, INV_SLOT_WIDTH * 4, INV_SLOT_HEIGHT * 7 );
//    rectangle( _info->rsMat, rect, CV_RGB( 255, 255, 255 ) );
//    Inventory *items = _info->invItems;
//    for( int item : items->keys() )
//    {
//        Scalar color;
//        if( items->value( item ) == 1 )
//            color = CV_RGB( 0, 255, 255 );
//        else if( items->value( item ) == 2 )
//            color = CV_RGB( 255, 0, 255 );
//        else if( items->value( item ) == 3 )
//            color = CV_RGB( 255, 255, 0 );
//        else if( items->value( item ) == 4 )
//            color = CV_RGB( 255, 255, 255 );
//        rectangle( _info->rsMat, Util::getInvSlotRect( item ), color );
//    }

//    putText(_info->rsMat, QString::number( items->size() ).toStdString(), Point( INV_SLOTS_X, INV_SLOTS_Y ), FONT_HERSHEY_DUPLEX, 1, Scalar( 255, 255, 255 ) );

    //////Run Modules
    if( !_init )
    {
        runModules( _modules.value( ModuleType::Init ) );
        _init = true;
    }
    runModules( _modules.value( ModuleType::Background ) );

    if( info->states.value( BotState::Pause ) )
    {
        if( info->pauseTimer->elapsed() > info->pauseLength )
        {
            info->pauseTimer->stop();
            info->states.insert( BotState::Pause, false );
        }
    }
    else if( info->states.value( BotState::Login ) )
        runModules( _modules.value( ModuleType::Login ) );
    else if( !info->states.value( BotState::Login ) )
    {
        //Ingame
        if( info->states.value( BotState::Banking ) )
            runModules( _modules.value( ModuleType::Banking ) );
        else
            runModules( _modules.value( ModuleType::Ingame ) );
    }

//    imshow( "filter", info->floodMat );
//    rectangle( info->rsMat, Util::getInvTabRect( Util::genRand( 1, 14 ) ), Scalar( 255, 255, 255 ) );

    return info->rsMat;
}

void BotInstance::runModules( QList<Module *> modules )
{
    for( Module *module : modules )
    {
        bool passedConditions = true;
        if( module->getConditions().size() > 0 )
        {
            passedConditions = false;
            int passes = 0;
            int passReq = module->getPassReq();
            if( passReq == 0 )
                passReq = module->getConditions().length();
            for( Condition *condition : module->getConditions() )
            {
                if( condition->checkCondition( info ) )
                    passes++;
                if( passes >= passReq )
                {
                    passedConditions = true;
                    break;
                }
            }
        }
        for( Task *task : passedConditions ? module->getTasks( false ) : module->getTasks( true ) )
        {
            task->execute( info );
        }
    }
}

void BotInstance::addModule( Module *module, ModuleType type )
{
    for( Condition *condition : module->getConditions() )
    {
        if( module->getTasks( true ).size() > 0 )
        {
            if( Condition* castTest = dynamic_cast<TimeoutCondition*>( condition ) )
            {
                qDebug() << "WARNING: TimeoutCondition with elseTask combination!";
            }
        }
    }

    _modules[ type ].push_back( module );
}

void BotInstance::addImage( int id, cv::Mat image )
{
    info->addImage( id, image );
}

void BotInstance::addColorItem( char color, int item )
{
    info->colorItems->insert( color, item );
}

BotInstance::~BotInstance()
{
    qDebug() << "Bot instance destroyed...";
}

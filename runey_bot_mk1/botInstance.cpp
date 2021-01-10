#include "botInstance.h"

using namespace cv;

BotInstance::BotInstance( int x, int y, StrPair loginInfo ) :
    loginInfo( loginInfo )
{
    info = new BotInfo;
    info->timer = new QElapsedTimer;
    info->x = x,
    info->y = y;
    info->timer->start();
}

Mat BotInstance::handleFrame( const cv::Mat &screen )
{
    //Prepare stuff for Modules
    info->rsMat = screen( Rect( info->x, info->y, RUNELITE_WIDTH, RUNELITE_HEIGHT ) ).clone();
    info->gameMat = info->rsMat( Rect( 0, 0, RS_INNER_WIDTH, RS_INNER_HEIGHT ) ).clone();
    info->invMat = info->rsMat( Rect( INV_SLOTS_X, INV_SLOTS_Y, INV_SLOT_WIDTH * 4, INV_SLOT_HEIGHT * 7 ) ).clone();
    info->tabId = TabCondition::getCurrentTab( info );

    info->states.insert( BotStates::Gather, false );

    for( int i = 0; i < 50; i++ )
    {
        if( info->rsMat.at<Vec3b>( GATHER_STATE_Y, GATHER_STATE_X + i )[1] == 255 )
        {
            info->states.insert( BotStates::Gather, true );
            break;
        }
    }

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

//    updateInventory( _info );
//    putText(_info->rsMat, QString::number( items->size() ).toStdString(), Point( INV_SLOTS_X, INV_SLOTS_Y ), FONT_HERSHEY_DUPLEX, 1, Scalar( 255, 255, 255 ) );

    //////Run Modules
    //Init
    if( !_init )
    {
        runModules( _initModules );
        _init = true;
    }
    else if( info->states.value( BotStates::Login ) && !info->states.value( BotStates::Pause ) )
        runModules( _loginModules );
    else if( !info->states.value( BotStates::Login ) )
        runModules( _modules );

//    imshow( "filter", info->floodMat );
    rectangle( info->rsMat, Util::getInvTabRect( Util::genRand( 1, 14 ) ), Scalar( 255, 255, 255 ) );

    return info->rsMat;
}

void BotInstance::runModules( QList<Module *> modules )
{
    for( Module *module : modules )
    {
        bool passedConditions = true;
        for( Condition *condition : module->getConditions() )
        {
            if( !condition->checkCondition( info ) )
            {
                passedConditions = false;
                break;
            }
        }
        for( Task *task : passedConditions ? module->getTasks( false ) : module->getTasks( true ) )
        {
            task->execute( info );
        }
    }
}

void BotInstance::addModule( Module *module, int type )
{
    if( type == 0 )
        _modules.push_back( module );
    else if( type == 1 )
        _initModules.push_back( module );
    else if( type == 2 )
        _loginModules.push_back( module );
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

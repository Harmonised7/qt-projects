#include "botInstance.h"

using namespace cv;

BotInstance::BotInstance( const int &x, const int &y )
{
    _info = new BotInfo;
    _info->timer = new QElapsedTimer;
    _info->x = x,
    _info->y = y;
    _info->timer->start();
}

Mat BotInstance::handleFrame( const cv::Mat &screen )
{
    //Prepare stuff for Modules
    _info->rsMat = screen( Rect( _info->x, _info->y, RUNELITE_WIDTH, RUNELITE_HEIGHT ) ).clone();
    _info->invMat = _info->rsMat( Rect( INV_SLOTS_X, INV_SLOTS_Y, INV_SLOT_WIDTH * 4, INV_SLOT_HEIGHT * 7 ) ).clone();
    Rect rect( INV_SLOTS_X, INV_SLOTS_Y, INV_SLOT_WIDTH * 4, INV_SLOT_HEIGHT * 7 );
    rectangle( _info->rsMat, rect, CV_RGB( 255, 255, 255 ) );
    _info->tabId = TabCondition::getCurrentTab( _info );

    _info->gatherState = false;

    for( int i = 0; i < 50; i++ )
    {
        if( _info->rsMat.at<Vec3b>( GATHER_STATE_Y, GATHER_STATE_X + i )[1] == 255 )
        {
            _info->gatherState = true;
            break;
        }
    }

    //Init
    if( !_init )
    {
        runModules( _initModules );
        _init = true;
    }

    //Draw stuff
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

    runModules( _modules );

//    imshow( "filter", info->floodMat );
    rectangle( _info->rsMat, Util::getInvTabRect( Util::genRand( 1, 14 ) ), Scalar( 255, 255, 255 ) );

    return _info->rsMat;
}

void BotInstance::runModules( QList<Module *> modules )
{
    for( Module *module : modules )
    {
        bool passedConditions = true;
        for( Condition *condition : module->getConditions() )
        {
            if( !condition->checkCondition( _info ) )
            {
                passedConditions = false;
                break;
            }
        }
        if( passedConditions )
        {
            for( Task *task : module->getTasks() )
            {
                task->execute( _info );
            }
        }
    }
}

void BotInstance::addModule( Module *module, bool initModule )
{
    if( initModule )
        _initModules.push_back( module );
    else
        _modules.push_back( module );
}

void BotInstance::addImage( int id, cv::Mat image )
{
    _info->addImage( id, image );
}

void BotInstance::addColorItem( char color, int item )
{
    _info->colorItems->insert( color, item );
}

BotInstance::~BotInstance()
{
    qDebug() << "Bot instance destroyed...";
}

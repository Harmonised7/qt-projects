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
    _info->rsMat = screen( Rect( _info->x, _info->y, RS_WIDTH, RS_HEIGHT ) ).clone();
    _info->invMat = _info->rsMat( Rect( INV_X, INV_Y, INV_SLOT_X * 4, INV_SLOT_Y * 7 ) ).clone();
    Rect rect( INV_X, INV_Y, INV_SLOT_X * 4, INV_SLOT_Y * 7 );
    rectangle( _info->rsMat, rect, CV_RGB( 255, 255, 255 ) );

    updateInventory( _info );
    BotInfo::updateFlood( _info->rsMat( Rect( BORDER_SIZE, BORDER_SIZE, RS_INNER_WIDTH, RS_INNER_HEIGHT ) ).clone(), &_info->rsFloodMatches );

    Inventory *items = _info->invItems;

    //draw stuff
    for( int item : items->keys() )
    {
        Scalar color;
        if( items->value( item ) == 1 )
            color = CV_RGB( 0, 255, 255 );
        else if( items->value( item ) == 2 )
            color = CV_RGB( 255, 0, 255 );
        else if( items->value( item ) == 3 )
            color = CV_RGB( 255, 255, 0 );
        else if( items->value( item ) == 4 )
            color = CV_RGB( 255, 255, 255 );
        rectangle( _info->rsMat, Util::getInvSlotRect( item ), color );
    }

    _info->gatherState = false;

    for( int i = 0; i < 50; i++ )
    {
        if( _info->rsMat.at<Vec3b>( GATHER_STATE_Y, GATHER_STATE_X + i )[1] == 255 )
        {
            _info->gatherState = true;
            break;
        }
    }

    putText(_info->rsMat, QString::number( items->size() ).toStdString(), Point( INV_X, INV_Y ), FONT_HERSHEY_DUPLEX, 1, Scalar( 255, 255, 255 ) );

    for( Module *module : _modules )
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

//    imshow( "filter", info->floodMat );

    return _info->rsMat;
}

void BotInstance::updateInventory( BotInfo *info )
{
    Mat ref = info->invMat.clone();
    Vec3b pixel;

    info->invItems->clear();
    //Color In Slot Finder
    for( int y = 0; y < 7; y++ )
    {
        for( int x = 0; x < 4; x++ )
        {
            for( int i = 0; i < INV_SLOT_Y; i++ )
            {
                for( int j = 0; j < INV_SLOT_X; j++ )
                {
                    pixel = ref.at<Vec3b>( y*INV_SLOT_Y+i, x*INV_SLOT_X+j );
                    if( pixel[0] == 255 )
                    {
                        info->invItems->insert( 1+y*4+x, info->colorItems->value( 'b' ) );
                        goto exit_pixel_loop;
                    }
                }
            }
            exit_pixel_loop:;
        }
    }

    //Set Images
    QMap<int, cv::Mat> images = info->getImages();
    for( int item : images.keys() )
    {
        Mat tpl = images.value( item ).clone();

        if (ref.empty() || tpl.empty())
        {
            qDebug() << "Error reading file(s)!" << endl;
            return;
        }

        //    imshow("file", ref);
        //    imshow("template", tpl);

        Mat res_32f(ref.rows - tpl.rows + 1, ref.cols - tpl.cols + 1, CV_32FC1);
        matchTemplate( ref, tpl, res_32f, TM_CCOEFF_NORMED );

        Mat res;
        res_32f.convertTo(res, CV_8U, 255.0);
        //    imshow("result", res);

        int size = ((tpl.cols + tpl.rows) / 4) * 2 + 1; //force size to be odd
        adaptiveThreshold(res, res, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, size, -128);
        //    imshow("result_thresh", res);

        while (true)
        {
            double minval, maxval, threshold = 0.9;
            Point minloc, maxloc;
            minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

            if (maxval >= threshold)
            {
                Rect match = Rect( maxloc, Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows) );
                int slot = Util::getInvSlotIndex( match );
                info->invItems->insert( slot, item );
                cv::putText( ref, QString::number( slot ).toStdString(), Util::QPointToPoint( Util::getMidPoint( match ) ), FONT_HERSHEY_DUPLEX, 1.0, CV_RGB( 255, 255, 255 ) );
                rectangle(ref, match, CV_RGB(0,255,0), 2);
                floodFill(res, maxloc, 0); //mark drawn blob
            }
            else
                break;
        }
        //    qDebug() << _info->invItems->size();
        //    imshow("final", ref);
    }
}

void BotInstance::addModule( Module *module )
{
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

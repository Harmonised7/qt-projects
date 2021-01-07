#include "botInstance.h"

using namespace cv;

BotInstance::BotInstance()
{
    _info = new BotInfo;
    _info->x = BAR_WIDTH + BORDER_SIZE,
    _info->y = 0;
}

BotInstance::BotInstance( const int &x, const int &y )
{
    _info = new BotInfo;
    _info->x = x,
    _info->y = y;
}

QPixmap BotInstance::handleFrame( const cv::Mat &screen )
{
    _info->rsMat = screen( Rect( _info->x, _info->y, RS_WIDTH, RS_HEIGHT ) ).clone();
    _info->invMat = _info->rsMat( Rect( INV_X, INV_Y, INV_SLOT_X * 4, INV_SLOT_Y * 7 ) ).clone();
    Rect rect( INV_X, INV_Y, INV_SLOT_X * 4, INV_SLOT_Y * 7 );
    rectangle( _info->rsMat, rect, CV_RGB( 255, 255, 255 ) );

    updateInventory( _info );
    updateFlood( _info );

    Inventory *items = _info->getItems();

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
        rectangle( _info->rsMat, Util::getInvSlotRect( item ), color );
    }

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

    return Util::matToPixmap( _info->rsMat );
}

void BotInstance::updateInventory( BotInfo *info )
{
    Mat ref = info->invMat.clone();
    QMap<int, cv::Mat> images = info->getImages();

    info->getItems()->clear();

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
                info->getItems()->insert( slot, item );
                cv::putText( ref, QString::number( slot ).toStdString(), Util::QPointToPoint( Util::getMidPoint( match ) ), FONT_HERSHEY_DUPLEX, 1.0, CV_RGB( 255, 255, 255 ) );
                rectangle(ref, match, CV_RGB(0,255,0), 2);
                floodFill(res, maxloc, 0); //mark drawn blob
            }
            else
                break;
        }
        //    qDebug() << _info->getItems()->size();
        //    imshow("final", ref);
    }
}

void BotInstance::updateFlood( BotInfo *info )
{
    Mat inputMat = info->rsMat( Rect( 4, 4, RS_INNER_WIDTH, RS_INNER_HEIGHT ) ).clone();
    Mat filteredMat = Mat( inputMat.rows, inputMat.cols, CV_8UC3, Scalar( 0, 0, 0 ) );
    QList<Point> strayPixels;

//    imshow( "raw", inputMat );

    for(int i = 0; i < inputMat.rows; i++)
    {
        for(int j = 0; j < inputMat.cols; j++)
        {
            Vec3b pixel = inputMat.at<Vec3b>(i, j);
            if( pixel[0] >= 150 && pixel[1] <= 10 && pixel[2] <= 10 )
                filteredMat.at<Vec3b>(i, j) = Vec3b( 255, 0, 0 );
        }
    }

    int matWidth = filteredMat.cols;
    int matHeight = filteredMat.rows;

    int x = 0, y = 0, lines = 0;
    for( Point p1 : strayPixels )
    {
        x += p1.x;
        y += p1.y;
        for( Point p2 : strayPixels )
        {
            if( ++lines < 100 && Util::getDistance( p1, p2 ) < 100 )
            {
                line( filteredMat, p1, p2, Scalar( 255, 0, 0 ), 3 );
            }
        }
    }

    Mat backupMat = filteredMat.clone();
    int bluePixels, attempts = 0;
    QPoint fillPoint = QPoint( 0, 0 );

    do
    {
        if( attempts > 0 )
            fillPoint = RndController::genRandPoint( QPoint( 0,0 ), QPoint( RS_INNER_WIDTH-5, RS_INNER_HEIGHT-5 ) );

        bluePixels = 0;
        filteredMat = backupMat.clone();
        floodFill( filteredMat, Point( fillPoint.x(), fillPoint.y() ), Scalar( 255, 0, 0 ) );
        for(int i = 0; i < matHeight; i++)
        {
            for(int j = 0; j < matWidth; j++)
            {
                if( filteredMat.at<Vec3b>( i, j )[0] == 0 )
                {
                    ++bluePixels;
                    filteredMat.at<Vec3b>( i, j ) = Vec3b( 255, 0, 0 );
                }
                else
                    filteredMat.at<Vec3b>( i, j ) = Vec3b( 0, 0, 0 );
            }
        }
        ++attempts;
    }
    while( attempts <= 5 && bluePixels > 0.7*matHeight*matWidth );

    imshow( "filter", filteredMat );
}

void BotInstance::addModule( Module *module )
{
    _modules.push_back( module );
}

void BotInstance::addImage( int id, cv::Mat image )
{
    _info->addImage( id, image );
}

BotInstance::~BotInstance()
{
    qDebug() << "Bot instance destroyed...";
}

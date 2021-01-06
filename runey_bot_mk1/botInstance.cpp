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

    updateInventory();

    //draw stuff
    for( int item : _info->getItems()->keys() )
    {
        rectangle( _info->rsMat, Util::getInvSlotRect( item ), CV_RGB( 255, 0, 255 ) );
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
//    updateInventory();

    return Util::matToPixmap( _info->rsMat );
}

void BotInstance::updateInventory()
{
    Mat ref = _info->invMat.clone();
    Mat tpl = ref( Rect( 0, 0, INV_SLOT_X, INV_SLOT_Y ) ).clone();

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

    _info->getItems()->clear();
    while (true)
    {
        double minval, maxval, threshold = 0.9;
        Point minloc, maxloc;
        minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

        if (maxval >= threshold)
        {
            Rect match = Rect( maxloc, Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows) );
            int slot = Util::getInvSlotIndex( match );
            (*_info->getItems())[ slot ] = 1;
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

void BotInstance::addModule( Module *module )
{
    _modules.push_back( module );
}

BotInstance::~BotInstance()
{
    qDebug() << "Bot instance destroyed...";
}

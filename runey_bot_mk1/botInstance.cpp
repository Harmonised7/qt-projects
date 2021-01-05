#include "botInstance.h"

using namespace cv;

MouseController BotInstance::_mc = MouseController( MOUSE_FPS, MOUSE_MIN, MOUSE_MAX, (double) MOUSE_JITTER, MOUSE_CURVES, MOUSE_SCREEN );

BotInstance::BotInstance() :
    _info( new BotInfo() )
{
    _info->x = BAR_WIDTH + BORDER_SIZE,
    _info->y = 0;
}

BotInstance::BotInstance( const int &x, const int &y ) :
    _info( new BotInfo() )
{
    _info->x = x,
    _info->y = y;
}

QPixmap BotInstance::handleFrame( const cv::Mat &screen )
{
    _info->rsMat = screen( Rect( _info->x, _info->y, RS_WIDTH, RS_HEIGHT ) ).clone();
    _info->invMat = _info->rsMat( Rect( INV_X, INV_Y, INV_SLOT_X * 4, INV_SLOT_Y * 7 ) ).clone();
    Rect rect( INV_X, INV_Y, INV_SLOT_X * 4, INV_SLOT_Y * 7 );
    rectangle( _info->rsMat, rect, CV_RGB( 255, 255, 255 ) );

//    for( int i = 0; i < 4; i++ )
//    {
//        for( int j = 0; j < 7; j++ )
//        {
//            _mc.mouseMove( rect.x, rect.y );
//        }
//    }

    rectangle( _info->rsMat, getInvSlotRect( RndController::genRand( 1, 28 ) ), CV_RGB( 255, 255, 255 ) );

    for( Condition *condition : _conditions )
    {
        if( condition->checkCondition( _info ) )
            condition->execute( _info );
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

    imshow("file", ref);
    imshow("template", tpl);

    Mat res_32f(ref.rows - tpl.rows + 1, ref.cols - tpl.cols + 1, CV_32FC1);
    matchTemplate( ref, tpl, res_32f, TM_CCOEFF_NORMED );

    Mat res;
    res_32f.convertTo(res, CV_8U, 255.0);
//    imshow("result", res);

    int size = ((tpl.cols + tpl.rows) / 4) * 2 + 1; //force size to be odd
    adaptiveThreshold(res, res, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, size, -128);
//    imshow("result_thresh", res);

    (*_info->getItems()).clear();
    while (true)
    {
        double minval, maxval, threshold = 0.9;
        Point minloc, maxloc;
        minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

        if (maxval >= threshold)
        {
            Rect match = Rect( maxloc, Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows) );
            int slot = getInvSlotIndex( match );
            (*_info->getItems())[ slot ] = 1;
            cv::putText( ref, QString::number( slot ).toStdString(), Util::QPointToPoint( Util::getMidPoint( match ) ), FONT_HERSHEY_DUPLEX, 1.0, CV_RGB( 255, 255, 255 ) );
            rectangle(ref, match, CV_RGB(0,255,0), 2);
            floodFill(res, maxloc, 0); //mark drawn blob
        }
        else
            break;
    }
    qDebug() << (*_info->getItems()).size();
    imshow("final", ref);
}

void BotInstance::dropItems()
{
    updateInventory();

    for( int i : BotInfo::_dropPatterns[ _randomNumbers.genRand( BotInfo::_dropPatterns.length() - 1 ) ] )
    {
        if( (*_info->getItems())[ i ] )
        {
            _mc.mousePress( MouseStates::Left, Util::getMidPoint( getInvSlotRect( i ) ) + QPoint( _info->x, _info->y ), 50, 75 );
        }
    }
}

void BotInstance::addCondition( Condition *condition )
{
    _conditions.push_back( condition );
}

cv::Rect BotInstance::getInvSlotRect( int index )
{
    if( index < 1 || index > 28 )
        qDebug() << "getInvSlotRect Index out of bounds!" << index;
    --index;
    return Rect( INV_X + (INV_SLOT_X * ( index % 4 ) ), INV_Y + (INV_SLOT_Y * ( index / 4 ) ), INV_SLOT_X, INV_SLOT_Y );
}

int BotInstance::getInvSlotIndex( const cv::Rect &rect )
{
    return getInvSlotIndex( Util::getMidPoint( rect ) ) + 1;
}

int BotInstance::getInvSlotIndex(const QPoint &point )
{
    return point.x() / INV_SLOT_X + (point.y() / INV_SLOT_Y) * 4;
}

BotInstance::~BotInstance()
{
    qDebug() << "Bot instance destroyed...";
}

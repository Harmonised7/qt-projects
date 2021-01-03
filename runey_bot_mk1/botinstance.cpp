#include "botinstance.h"

using namespace cv;

MouseController BotInstance::_mc = MouseController( MOUSE_FPS, MOUSE_MIN, MOUSE_MAX, (double) MOUSE_JITTER, MOUSE_CURVES, MOUSE_SCREEN );
DropPatterns BotInstance::_dropPatterns = DropPatterns
{
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28 },
    { 1, 5, 9, 13, 17, 21, 25, 2, 6, 10, 14, 18, 22, 26, 3, 7, 11, 15, 19, 23, 27, 4, 8, 12, 16, 20, 24, 28 },
    { 1, 2, 5, 6, 9, 10, 13, 14, 17, 18, 21, 22, 25, 26, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23, 24, 27, 28 }
};

BotInstance::BotInstance() :
    _x(BAR_WIDTH + BORDER_SIZE),
    _y(0)
{

}

BotInstance::BotInstance( const int &x, const int &y ) :
    _x( x ),
    _y( y )
{
}

QPixmap BotInstance::handleFrame( const cv::Mat &screen )
{
    _rsMat = screen( Rect( _x, _y, RS_WIDTH, RS_HEIGHT ) ).clone();
    _invMat = _rsMat( Rect( INV_X, INV_Y, INV_SLOT_X * 4, INV_SLOT_Y * 7 ) ).clone();
    Rect rect( INV_X, INV_Y, INV_SLOT_X * 4, INV_SLOT_Y * 7 );
    rectangle( _rsMat, rect, CV_RGB( 255, 255, 255 ) );

//    for( int i = 0; i < 4; i++ )
//    {
//        for( int j = 0; j < 7; j++ )
//        {
//            _mc.mouseMove( rect.x, rect.y );
//        }
//    }

    rectangle( _rsMat, getInvSlotRect( RndController::genRand( 1, 28 ) ), CV_RGB( 255, 255, 255 ) );

//    updateInventory();

    return Util::matToPixmap( _rsMat );
}

void BotInstance::updateInventory()
{
    Mat ref = _invMat.clone();
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

    _invItems.clear();
    while (true)
    {
        double minval, maxval, threshold = 0.9;
        Point minloc, maxloc;
        minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

        if (maxval >= threshold)
        {
            Rect match = Rect( maxloc, Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows) );
            int slot = getInvSlotIndex( match );
            _invItems[ slot ] = 1;
            cv::putText( ref, QString::number( slot ).toStdString(), Util::QPointToPoint( Util::getMidPoint( match ) ), FONT_HERSHEY_DUPLEX, 1.0, CV_RGB( 255, 255, 255 ) );
            rectangle(ref, match, CV_RGB(0,255,0), 2);
            floodFill(res, maxloc, 0); //mark drawn blob
        }
        else
            break;
    }
    qDebug() << _invItems.size();
    imshow("final", ref);
}

void BotInstance::dropItems()
{
    updateInventory();

    for( int i : _dropPatterns[ _randomNumbers.genRand( _dropPatterns.length() - 1 ) ] )
    {
        if( _invItems[ i ] )
        {
            _mc.mousePress( MouseStates::Left, Util::getMidPoint( getInvSlotRect( i ) ) + QPoint( _x, _y ), 50, 75 );
        }
    }
}

cv::Rect BotInstance::getInvSlotRect( int index )
{
    if( index < 1 || index > 28 )
        qDebug() << "getInvSlotRect Index out of bounds!" << index;
    index--;
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

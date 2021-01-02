#include "botinstance.h"

using namespace cv;

MouseController BotInstance::_mc = MouseController( MOUSE_FPS, MOUSE_MIN, MOUSE_MAX, (double) MOUSE_JITTER, MOUSE_CURVES, MOUSE_SCREEN );

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

QPixmap BotInstance::handleFrame( Mat screen )
{
    _rsMat = screen( Rect( _x, _y, RS_WIDTH, RS_HEIGHT ) ).clone();
    _invMat = _rsMat( Rect( INV_X, INV_Y, INV_SLOT_X * 4, INV_SLOT_Y * 7 ) ).clone();

    Rect rect( INV_X, INV_Y, INV_SLOT_X * 4, INV_SLOT_Y * 7 );
    rectangle( _rsMat, rect, CV_RGB( 255, 255, 255 ) );

    for( int i = 0; i < 4; i++ )
    {
        for( int j = 0; j < 7; j++ )
        {
//            rectangle( _rsMat, getInvSlotRect( RndController::genRand( 1, 28 ) ), CV_RGB( 255, 255, 255 ) );
//            _mc.mouseMove( rect.x, rect.y );
        }
    }

    updateInventory();

    return Util::matToPixmap( _rsMat );
}

void BotInstance::updateInventory()
{
    Mat ref = _invMat;
    Mat tpl = _invMat( Rect( 0, 0, INV_SLOT_X, INV_SLOT_Y ) ).clone();
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

    this->matches = 0;
    while (true)
    {
        double minval, maxval, threshold = 0.9;
        Point minloc, maxloc;
        minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

        if (maxval >= threshold)
        {
            this->matches++;
            rectangle(ref, maxloc, Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows), CV_RGB(0,255,0), 2);
            floodFill(res, maxloc, 0); //mark drawn blob
        }
        else
            break;
    }
    imshow("final", ref);
}

cv::Rect BotInstance::getInvSlotRect( int index )
{
    if( index < 1 || index > 28 )
        qDebug() << "getInvSlotRect Index out of bounds!" << index;
    index--;
    return Rect( INV_X + (INV_SLOT_X * ( index % 4 ) ), INV_Y + (INV_SLOT_Y * ( index / 4 ) ), INV_SLOT_X, INV_SLOT_Y );
}

#include "botinfo.h"

using namespace cv;

DropPatterns BotInfo::_dropPatterns = DropPatterns
{
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
    {1, 5, 9, 13, 17, 21, 25, 2, 6, 10, 14, 18, 22, 26, 3, 7, 11, 15, 19, 23, 27, 4, 8, 12, 16, 20, 24, 28},
    {1, 5, 9, 13, 17, 21, 25, 26, 22, 18, 14, 10, 6, 2, 3, 7, 11, 15, 19, 23, 27, 28, 24, 20, 16, 12, 8, 4},
    {1, 2, 3, 4, 8, 7, 6, 5, 9, 10, 11, 12, 16, 15, 14, 13, 17, 18, 19, 20, 20, 23, 22, 21, 25, 26, 27, 28},
    {1, 2, 5, 6, 9, 10, 13, 14, 17, 18, 21, 22, 25, 26, 3, 4, 7, 8 ,11, 12, 15, 16, 19, 20, 23, 24, 27, 28},
    {1, 2, 5, 6, 9, 10, 13, 14, 17, 18, 21, 22, 25, 26, 27, 28, 23, 24, 19, 20, 15, 16, 11, 12, 7, 8, 3, 4},
    {1, 5, 9, 13, 17, 21, 25, 26, 27, 28, 24, 20, 16, 12, 8, 4, 3, 7, 11, 15, 19, 23, 22, 18, 14, 10, 6, 2},
    {1, 5, 9, 13, 17, 21, 25, 26, 27, 28, 24, 20, 16, 12, 8, 4, 2, 6, 10, 14, 18, 22, 23, 19, 15, 11, 7, 3}
};

BotInfo::BotInfo()
{
    invItems = new Inventory();
    colorItems = new QMap<char, int>();
}

BotInfo::~BotInfo()
{
    qDebug() << "botInfo killed";
}

void BotInfo::addImage( const int &id, const cv::Mat image )
{
    _images.insert( id, image );
}

QMap<int, cv::Mat> BotInfo::getImages()
{
    return _images;
}

void BotInfo::updateFlood( Mat inputMat, QSet<QPoint *> *floodMatches )
{
    Mat floodMat = Mat( inputMat.rows, inputMat.cols, CV_8UC3, Scalar( 0, 0, 0 ) );
    QList<Point> strayPixels;

//    imshow( "raw", inputMat );

    for(int i = 0; i < inputMat.rows; i++)
    {
        for(int j = 0; j < inputMat.cols; j++)
        {
            Vec3b pixel = inputMat.at<Vec3b>(i, j);
            if( pixel[0] >= 150 && pixel[1] <= 10 && pixel[2] <= 10 )
                floodMat.at<Vec3b>(i, j) = Vec3b( 255, 255, 255 );
        }
    }

    int matWidth = floodMat.cols;
    int matHeight = floodMat.rows;

    Mat backupMat = floodMat.clone();
    int attempts = 0;
    QPoint fillPoint = QPoint( 0, 0 );

    do
    {
        if( attempts > 0 )
            fillPoint = Util::genRandQPoint( QPoint( 0,0 ), QPoint( RS_INNER_WIDTH, RS_INNER_HEIGHT ) );

        floodMatches->clear();
        floodMat = backupMat.clone();
        floodFill( floodMat, Point( fillPoint.x(), fillPoint.y() ), Scalar( 255, 255, 255 ) );
        for(int i = 0; i < matHeight; i++)
        {
            for(int j = 0; j < matWidth; j++)
            {
                if( floodMat.at<Vec3b>( i, j )[0] == 0 )
                {
                    floodMatches->insert( new QPoint( j, i ) );
                    floodMat.at<Vec3b>( i, j ) = Vec3b( 255, 255, 255 );
                }
                else
                    floodMat.at<Vec3b>( i, j ) = Vec3b( 0, 0, 0 );
            }
        }
        ++attempts;
    }
    while( attempts <= 5 && floodMatches->size() > 0.7*matHeight*matWidth );
}

void BotInfo::updateInventory( BotInfo *info )
{
    Mat ref = info->invMat.clone();
    Vec3b pixel;

    info->invItems->clear();
    //Color In Slot Finder
    for( int y = 0; y < 7; y++ )
    {
        for( int x = 0; x < 4; x++ )
        {
            for( int i = 0; i < INV_SLOT_HEIGHT; i++ )
            {
                for( int j = 0; j < INV_SLOT_WIDTH; j++ )
                {
                    pixel = ref.at<Vec3b>( y*INV_SLOT_HEIGHT+i, x*INV_SLOT_WIDTH+j );
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

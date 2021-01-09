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
            fillPoint = Util::genRandQPoint( QPoint( 0,0 ), QPoint( RS_INNER_WIDTH-5, RS_INNER_HEIGHT-5 ) );

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

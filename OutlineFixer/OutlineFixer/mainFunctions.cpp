#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "util.h"

using namespace cv;

void MainWindow::init()
{
    connect( &_refreshTimer, SIGNAL( timeout() ), this, SLOT( handleFrame() ) );
    _refreshTimer.start( 1000 / FPS );
}

void MainWindow::handleFrame()
{
    Mat inputMat = Util::pixMapToMat( QPixmap( ":/screenshots/images/image.png" ) );
    Mat filteredMat = Mat( inputMat.rows, inputMat.cols, CV_8UC3, Scalar( 0, 0, 0 ) );
    imshow( "input", inputMat );
    QList<Point> strayPixels;

    for(int i = 0; i < inputMat.rows; i++)
    {
        for(int j = 0; j < inputMat.cols; j++)
        {
            Vec3b pixel = inputMat.at<Vec3b>(i, j);
            if( pixel[0] >= 200 && pixel[1] <= 10 && pixel[2] <= 10 )
                filteredMat.at<Vec3b>(i, j) = Vec3b( 255, 0, 0 );
        }
    }

    int matWidth = filteredMat.cols;
    int matHeight = filteredMat.rows;

    int skipped = 0, bluePixels = 0;

    for(int i = 0; i < matHeight; i++)
    {
        for(int j = 0; j < matWidth; j++)
        {
            Vec3b midPixel = filteredMat.at<Vec3b>( i, j );
            if( midPixel[0] < 255 )
            {
                ++skipped;
                continue;
            }

            ++bluePixels;

            for( int y = -2; y <= 2; y++ )
            {
                for( int x = -2; x <= 2; x++ )
                {
                    if( j + x < 0 || j + x > matWidth || i + y < 0 || i + y > matHeight )
                    {
                        qDebug() << j << matWidth << "|" << i << matHeight;
//                        rectangle( filteredMat, Point( j - 2, i - 2 ), Point( j + 2, i + 2 ), Scalar( 0, 255, 255 ) );
                        strayPixels.push_back( Point( j, i ) );
                        goto in_loop_end;
                    }
                }
            }
            in_loop_end:;
        }
    }

    int x = 0, y = 0;
    for( Point p : strayPixels )
    {
        x += p.x;
        y += p.y;
    }

    x /= strayPixels.size();
    y /= strayPixels.size();

    floodFill( filteredMat, Point( x, y ), Scalar( 255, 0, 0 ) );

    imshow( "filter", filteredMat );

    qDebug() << "skipped: " << skipped;
    qDebug() << "blue pixels: " << bluePixels;
    qDebug() << "Stray Pixels:" << strayPixels.size();
}

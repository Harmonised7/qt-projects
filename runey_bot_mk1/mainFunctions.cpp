#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

void MainWindow::init()
{
    connect( &_refreshTimer, SIGNAL( timeout() ), this, SLOT( handleFrame() ) );
    _refreshTimer.start( 1000 / FPS );
}

void MainWindow::handleFrame()
{
    _screenPixMat = pixMapToMat( qApp->screens().at(0)->grabWindow( QDesktopWidget().winId() ) );
    _rsMat = _screenPixMat( Rect( BAR_WIDTH + BORDER_SIZE, _screenPixMat.rows - RS_HEIGHT - BORDER_SIZE, RS_WIDTH, RS_HEIGHT ) ).clone();
    _invMat = _rsMat( Rect( INV_X, INV_Y, INV_SLOT_X * 4, INV_SLOT_Y * 7 ) ).clone();
//    cv::resize( _croppedRsMat, _croppedRsMat, Size( ui->videoLabel->width(), ui->videoLabel->width() * _screenPixMap.height() / _screenPixMap.width()) );

    Rect rect( INV_X, INV_Y, INV_SLOT_X * 4, INV_SLOT_Y * 7 );
    rectangle( _rsMat, rect, CV_RGB( 255, 255, 255 ) );

    QProcess *process = new QProcess(this);
    process->start( QString( "xdotool key " ) );

    ui->videoLabel->setPixmap( matToPixmap( _rsMat ) );
}

QPixmap MainWindow::matToPixmap(const Mat &openCVMat)
{
    return QPixmap::fromImage( QImage(static_cast<const unsigned char*>(openCVMat.data), openCVMat.cols, openCVMat.rows, static_cast<int>(openCVMat.step), QImage::Format_RGB888).rgbSwapped() );
}

Mat MainWindow::pixMapToMat(const QPixmap &QtPixmap)
{
    QImage _tempImage = pixmapToQImage(QtPixmap);

    Mat _tempMat = Mat( _tempImage.height(), _tempImage.width(), CV_8UC4, const_cast<uchar*>(_tempImage.bits()), static_cast<size_t>(_tempImage.bytesPerLine()) );
    cvtColor( _tempMat, _tempMat, COLOR_BGRA2BGR );

    return _tempMat;
}

QImage MainWindow::pixmapToQImage(const QPixmap &QtPixmap)
{
    return QtPixmap.toImage();
}

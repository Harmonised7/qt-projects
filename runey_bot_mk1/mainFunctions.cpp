#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

QPixmap MainWindow::matToPixmap(const Mat &openCVMat)
{
    return QPixmap::fromImage( QImage(static_cast<const unsigned char*>(openCVMat.data), openCVMat.cols, openCVMat.rows, static_cast<int>(openCVMat.step), QImage::Format_RGB888).rgbSwapped() );
}

Mat MainWindow::pixmapToMat(const QPixmap &QtPixmap)
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

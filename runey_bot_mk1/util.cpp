#include "util.h"

using namespace cv;

QPoint Util::getMidPoint( cv::Rect area )
{
    return QPoint( area.tl().x + area.width / 2, area.tl().y + area.height / 2 );
}

int Util::makeAbsolute( int value )
{
    return value > 0 ? value : -value;
}

QPoint Util::getMidPoint( QPoint p1, QPoint p2 )
{
    return QPoint( ( p1.x() + p2.x() ) / 2, ( p1.y() + p2.y() ) / 2 );
}

QPixmap Util::matToPixmap(const Mat &openCVMat)
{
    return QPixmap::fromImage( QImage(static_cast<const unsigned char*>(openCVMat.data), openCVMat.cols, openCVMat.rows, static_cast<int>(openCVMat.step), QImage::Format_RGB888).rgbSwapped() );
}

Mat Util::pixMapToMat(const QPixmap &QtPixmap)
{
    QImage _tempImage = pixmapToQImage(QtPixmap);

    Mat _tempMat = Mat( _tempImage.height(), _tempImage.width(), CV_8UC4, const_cast<uchar*>(_tempImage.bits()), static_cast<size_t>(_tempImage.bytesPerLine()) );
    cvtColor( _tempMat, _tempMat, COLOR_BGRA2BGR );

    return _tempMat;
}

QImage Util::pixmapToQImage(const QPixmap &QtPixmap)
{
    return QtPixmap.toImage();
}

#include "util.h"

using namespace cv;

Point Util::QPointToPoint( QPoint point )
{
    return Point( point.x(), point.y() );
}


QPoint Util::getMidPoint( cv::Rect area )
{
    return QPoint( area.tl().x + area.width / 2, area.tl().y + area.height / 2 );
}

cv::Rect Util::getInvSlotRect( int index )
{
    if( index < 1 || index > 28 )
        qDebug() << "getInvSlotRect Index out of bounds!" << index;
    --index;
    return Rect( INV_SLOT_SHRINK + INV_X + (INV_SLOT_X * ( index % 4 ) ),
                 INV_SLOT_SHRINK + INV_Y + (INV_SLOT_Y * ( index / 4 ) ),
                 INV_SLOT_X - INV_SLOT_SHRINK*2,
                 INV_SLOT_Y - INV_SLOT_SHRINK*2 );
}

int Util::getInvSlotIndex( const cv::Rect &rect )
{
    return getInvSlotIndex( Util::getMidPoint( rect ) ) + 1;
}

int Util::getInvSlotIndex(const QPoint &point )
{
    return point.x() / INV_SLOT_X + (point.y() / INV_SLOT_Y) * 4;
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

double Util::map(const double &x, const double &in_min, const double &in_max, const double &out_min, const double &out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double Util::mapCapped(const double &x, const double &in_min, const double &in_max, const double &out_min, const double &out_max)
{
    return cap( (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min, in_min, in_max );
}

double Util::cap( const double &x, const double &min_bound, const double &max_bound )
{
    if( max_bound > min_bound )
        return max( min_bound, min( max_bound, x ) );
    else
        return max( max_bound, min( min_bound, x ) );
}

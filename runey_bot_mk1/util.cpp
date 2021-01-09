#include "util.h"

using namespace cv;

Point Util::QPointToPoint( QPoint point )
{
    return Point( point.x(), point.y() );
}

QPoint Util::PointToQPoint( Point point )
{
    return QPoint( point.x, point.y );
}

Rect Util::RectFromTwoQPoints( QPoint p1, QPoint p2 )
{
    return Rect( QPointToPoint( p1 ), QPointToPoint( p2 ) );
}

QPoint Util::getMidPoint( Rect area )
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

double Util::getDistance( Point &p1, Point &p2 )
{
    return qSqrt( qPow( p2.x - p1.x, 2 ) + qPow( p2.y - p1.y, 2 ) );
}

double Util::getDistance( QPoint &p1, QPoint &p2 )
{
    return qSqrt( qPow( p2.x() - p1.x(), 2 ) + qPow( p2.y() - p1.y(), 2 ) );
}

int Util::genRand( int min, int max )
{
    if( min == max )
        return min;
    else if( max > min )
        return QRandomGenerator::global()->bounded( min, max + 1 );
    else
        return QRandomGenerator::global()->bounded( max, min + 1 );
}

double Util::genRandDouble( double min, double max )
{
    if( min == max )
        return min;
    else if( max > min )
        return min + QRandomGenerator::global()->bounded( max - min );
    else
        return max + QRandomGenerator::global()->bounded( min - max );
}

QPoint Util::genRandQPoint( cv::Rect area )
{
    return genRandQPoint( QPoint( area.tl().x, area.tl().y ), QPoint( area.br().x, area.br().y ) );
}

Point Util::genRandPoint( cv::Rect area )
{
    return genRandPoint( Point( area.tl().x, area.tl().y ), Point( area.br().x, area.br().y ) );
}

QPoint Util::genRandQPoint( cv::Mat mat )
{
    return genRandQPoint( QPoint( 0, 0 ), QPoint( mat.cols, mat.rows ) );
}

Point Util::genRandPoint( cv::Mat mat )
{
    return genRandPoint( Point( 0, 0 ), Point( mat.cols, mat.rows ) );
}

//QPoint Util::genRandPointOfColor( cv::Mat mat, cv::Vec3b color, int attempts )
//{
//    int x, y;
//    int cols = mat.cols;
//    int rows = mat.rows;
//    Vec3b *tempColor;

//    for( int i = 0; i < attempts; i++ )
//    {
//        x = genRand( cols );
//        y = genRand( rows );
//        tempColor = &mat.at<Vec3b>( x, y );
//        if( *tempColor == color )
//            return QPoint( x, y );
//    }

//    qDebug() << "Could not find a point in" << attempts << "attempts";
//    return QPoint( -1, -1 );
//}

QPoint Util::genRandQPoint( QPoint p1, QPoint p2 )
{
    return QPoint( p1.x() + genRand( p2.x() - p1.x() ), p1.y() + genRand( p2.y() - p1.y() ) );
}

Point Util::genRandPoint( Point p1, Point p2 )
{
    return Point( p1.x + genRand( p2.x - p1.x ), p1.y + genRand( p2.y - p1.y ) );
}

QPoint Util::genRandQPointOffset( QPoint p, int offset )
{
    return p + QPoint( genRand( -offset, offset ), genRand( -offset, offset ) );
}

Point Util::genRandPointOffset( Point p, int offset )
{
    return p + Point( genRand( -offset, offset ), genRand( -offset, offset ) );
}

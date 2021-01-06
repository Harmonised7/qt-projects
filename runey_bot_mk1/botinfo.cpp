#include "botinfo.h"

DropPatterns BotInfo::_dropPatterns = DropPatterns
{
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28 },
    { 1, 5, 9, 13, 17, 21, 25, 2, 6, 10, 14, 18, 22, 26, 3, 7, 11, 15, 19, 23, 27, 4, 8, 12, 16, 20, 24, 28 },
    { 1, 2, 5, 6, 9, 10, 13, 14, 17, 18, 21, 22, 25, 26, 3, 4, 7, 8, 11, 12, 15, 16, 19, 20, 23, 24, 27, 28 }
};

BotInfo::BotInfo()
{
    _invItems = new Inventory();
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

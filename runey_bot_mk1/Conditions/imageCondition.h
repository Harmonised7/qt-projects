#ifndef IMAGECONDITION_H
#define IMAGECONDITION_H

#include "Conditions/condition.h"

class ImageCondition : public Condition
{
public:
    ImageCondition( cv::Mat mat, double threshold = DEFAULT_THRESHOLD );
    ImageCondition( QList<MatDoublePair> mats );

    bool checkCondition( BotInfo *info );

private:
    QList<MatDoublePair> _mats;
};

#endif // IMAGECONDITION_H

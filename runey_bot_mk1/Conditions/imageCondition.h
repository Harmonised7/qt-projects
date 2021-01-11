#ifndef IMAGECONDITION_H
#define IMAGECONDITION_H

#include "Conditions/condition.h"

class ImageCondition : public Condition
{
public:
    ImageCondition( cv::Mat mat, double threshold = DEFAULT_THRESHOLD );
    ImageCondition( QList<MatDoublePair> mats );

    bool checkCondition( BotInfo *info ) override;

    void setCrop( cv::Rect crop );

private:
    QList<MatDoublePair> _mats;
    cv::Rect _crop;
    bool _cropSet = false;
};

#endif // IMAGECONDITION_H

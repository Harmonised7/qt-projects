#ifndef CLICKIMAGESTASK_H
#define CLICKIMAGESTASK_H

#include "Tasks/task.h"

class ClickImagesTask : public Task
{
public:
    ClickImagesTask( cv::Mat mat, double threshold = DEFAULT_THRESHOLD );
    ClickImagesTask( QList<cv::Mat> mats );
    ClickImagesTask( QList<MatDoublePair> mats );

    void execute( BotInfo *info ) override;

    void setCrop( cv::Rect crop );

private:
    QList<MatDoublePair> _mats = QList<MatDoublePair>();
    cv::Rect _crop;
    QPoint _cropOffset = QPoint( 0, 0 );
    bool _cropSet = false;
};

#endif // CLICKIMAGESTASK_H

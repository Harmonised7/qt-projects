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

private:
    QList<MatDoublePair> _mats = QList<MatDoublePair>();
};

#endif // CLICKIMAGESTASK_H

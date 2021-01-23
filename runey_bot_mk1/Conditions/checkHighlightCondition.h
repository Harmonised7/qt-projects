#ifndef CHECKHIGHLIGHTCONDITION_H
#define CHECKHIGHLIGHTCONDITION_H

#include "Conditions/condition.h"

class CheckHighlightCondition : public Condition
{
public:
    CheckHighlightCondition( bool type, cv::Vec3b pixel );
    CheckHighlightCondition( bool type, cv::Vec3b p1, cv::Vec3b p2 );

    bool checkCondition( BotInfo *info ) override;

private:
    bool _type;
    cv::Vec3b _p1, _p2;
};

#endif // CHECKHIGHLIGHTCONDITION_H

#ifndef MODULE_H
#define MODULE_H

#include <QList>

#include "Conditions/condition.h"
#include "Tasks/task.h"

class Module
{
public:
    Module( QList<Condition *> conditions, QList<Task *> tasks, QList<Task *> elseTasks = QList<Task *>() );
    Module( Condition *condition, Task *task );
    Module( Task *task );

    void addCondition( Condition *condition );
    void addTask( Task *task, bool elseTask = false );
    void setMatchReq( unsigned int matchReq );
    unsigned int getPassReq();

    QList<Condition *> getConditions();
    QList<Task *> getTasks( bool elseTask = false );

private:
    QList<Condition *> _conditions;
    QList<Task *> _tasks;
    QList<Task *> _elseTasks;
    unsigned int _passReq = 0;
};

#endif // MODULE_H

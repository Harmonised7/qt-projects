#ifndef MODULE_H
#define MODULE_H

#include <QList>

#include "Conditions/condition.h"
#include "Tasks/task.h"

class Module
{
public:
    Module( QList<Condition *> conditions, QList<Task *> tasks );
    Module( Condition *condition, Task *task );
    Module( Task *task );

    void addCondition( Condition *condition );
    void addTask( Task *task );

    QList<Condition *> getConditions();
    QList<Task *> getTasks();

private:
    QList<Condition *> _conditions;
    QList<Task *> _tasks;
};

#endif // MODULE_H

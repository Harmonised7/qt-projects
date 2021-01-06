#include "module.h"

Module::Module( QList<Condition *> conditions, QList<Task *> tasks )
{
    _conditions = conditions;
    _tasks = tasks;
}

Module::Module( Condition *condition, Task *task )
{
    _conditions = QList<Condition *>();
    _conditions.push_back( condition );

    _tasks = QList<Task *>();
    _tasks.push_back( task );
}

void Module::addCondition( Condition *condition )
{
    _conditions.push_back( condition );
}

void Module::addTask( Task *task )
{
    _tasks.push_back( task );
}

QList<Condition *> Module::getConditions()
{
    return _conditions;
}

QList<Task *> Module::getTasks()
{
    return _tasks;
}

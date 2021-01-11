#include "module.h"

Module::Module( QList<Condition *> conditions, QList<Task *> tasks, QList<Task *> elseTasks ) :
    _conditions( conditions ),
    _tasks( tasks ),
    _elseTasks( elseTasks )
{
}

Module::Module( Condition *condition, Task *task )
{
    _conditions = QList<Condition *>();
    _conditions.push_back( condition );

    _tasks = QList<Task *>();
    _tasks.push_back( task );
}

Module::Module( Task *task )
{
    _conditions = QList<Condition *>();

    _tasks = QList<Task *>();
    _tasks.push_back( task );
}

void Module::addCondition( Condition *condition )
{
    _conditions.push_back( condition );
}

void Module::addTask( Task *task, bool elseTask )
{
    ( elseTask ? _elseTasks : _tasks ).push_back( task );
}

QList<Task *> Module::getTasks( bool elseTask )
{
    return elseTask ? _elseTasks : _tasks;
}

void Module::setMatchReq( unsigned int matchReq )
{
    _passReq = matchReq;
}

unsigned int Module::getPassReq()
{
    return _passReq;
}

QList<Condition *> Module::getConditions()
{
    return _conditions;
}

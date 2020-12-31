//
// Created by weining on 31/12/20.
//

#include "myLib.hh"
#include <headerOnlyLibC.hh>

common::Task myLib::createTask( int x )
{
    common::Task task{ x };
    common::pushBackTask( task );
    return task;
}

std::vector< common::Task > myLib::createTask3( int x, int y, int z )
{
    auto ts = libC::createTasks( x, y, z );
    size_t sz{ 0 };
    for ( const auto &t : ts )
    {
        sz = common::pushBackTask( t );
    }
    return ts;
}

//
// Created by weining on 31/12/20.
//

#ifndef C_DESIGNPATTERNS_HEADERONLYLIBC_HH
#define C_DESIGNPATTERNS_HEADERONLYLIBC_HH

#include <common.hh>
#include <vector>

namespace
{
template < typename... Ts >
void createTasks( std::vector< common::Task > o_tasks, Ts... params )
{
    ( o_tasks.emplace_back( params ), ... );
}
}  // namespace

namespace libC
{
template < typename... Ts >
std::vector< common::Task > createTasks( Ts... params )
{
    std::vector< common::Task > xs;
    ::createTasks( xs, std::forward< Ts >( params )... );
    return xs;
}
}  // namespace libC

#endif  // C_DESIGNPATTERNS_HEADERONLYLIBC_HH

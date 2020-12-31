//
// Created by weining on 31/12/20.
//

#ifndef C_DESIGNPATTERNS_COMMON_HH
#define C_DESIGNPATTERNS_COMMON_HH

#include <deque>
#include <optional>

namespace common
{
using Task = int;
}

namespace
{
struct GlobalState
{
    std::deque< common::Task > tasks;
};

inline static GlobalState state{};

}  // namespace

namespace common
{
inline size_t pushBackTask( const Task& newTask )
{
    ::state.tasks.push_back( newTask );
    return ::state.tasks.size();
}

inline std::optional< Task > tryPopFront()
{
    if ( ::state.tasks.empty() )
    {
        return std::nullopt;
    }
    Task front{ ::state.tasks.front() };
    ::state.tasks.pop_front();
    return front;
}

inline size_t numTasks()
{
    return ::state.tasks.size();
}
}  // namespace common

#endif  // C_DESIGNPATTERNS_COMMON_HH

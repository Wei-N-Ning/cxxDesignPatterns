//
// Created by weining on 31/12/20.
//

#ifndef C_DESIGNPATTERNS_MYLIB_HH
#define C_DESIGNPATTERNS_MYLIB_HH

#include <vector>

#include "common.hh"

namespace myLib
{
common::Task createTask( int x );
std::vector< common::Task > createTask3( int x, int y, int z );
}  // namespace myLib

#endif  // C_DESIGNPATTERNS_MYLIB_HH

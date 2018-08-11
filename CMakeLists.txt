cmake_minimum_required(VERSION 3.8)
project(C++DesignPatterns)

include(_cmake/tinyCUnit.cmake)

enable_testing()

add_subdirectory(commands)
add_subdirectory(functors)
add_subdirectory(memory)
add_subdirectory(pimpl)
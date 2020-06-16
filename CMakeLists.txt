cmake_minimum_required(VERSION 3.8)

set(CMAKE_C_COMPILER gcc-9)
set(CMAKE_CXX_COMPILER g++-9)

project(C++DesignPatterns)

include(tinyCUnit/tinyCUnit.cmake)

enable_testing()

add_subdirectory(commands)
add_subdirectory(functors)
add_subdirectory(memory)
add_subdirectory(pimpl)
add_subdirectory(NVI)
add_subdirectory(exceptionSafety)
add_subdirectory(inTermsOf)

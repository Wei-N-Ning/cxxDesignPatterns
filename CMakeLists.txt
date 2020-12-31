cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER gcc-10)
set(CMAKE_CXX_COMPILER g++-10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(C++DesignPatterns)

include(tinyCUnit/tinyCUnit.cmake)

add_subdirectory(3rdParty/autotimer)
add_subdirectory(3rdParty/doctest)
enable_testing()

add_subdirectory(commands)
add_subdirectory(functionObjects)
add_subdirectory(memory)
add_subdirectory(pimpl)
add_subdirectory(NVI)
add_subdirectory(exceptionSafety)
add_subdirectory(inTermsOf)
add_subdirectory(headerOnlyLib)
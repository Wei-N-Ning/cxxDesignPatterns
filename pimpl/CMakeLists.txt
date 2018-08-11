
add_library(foo STATIC
    fooService.cpp
    fooService.hpp)
set_target_properties(foo
    PROPERTIES
    CXX_STANDARD 14)
target_include_directories(foo
    PUBLIC
    .)

add_executable(test_foo test_fooService.cpp)
set_target_properties(test_foo
    PROPERTIES
    CXX_STANDARD 14)
target_link_libraries(test_foo foo)
add_test(
    NAME "pimpl::test_foo"
    COMMAND test_foo)

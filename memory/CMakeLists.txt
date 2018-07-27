
add_tinytest_executable(test_objectPool
    test_objectPool.cpp)
target_sources(test_objectPool
    PRIVATE
    objectPool.hpp)
set_target_properties(test_objectPool
    PROPERTIES
    CXX_STANDARD 14)
add_test(
    NAME "memory:test_objectPool"
    COMMAND test_objectPool)

add_tinytest_executable(test_page
    test_page.cpp)
target_sources(test_page
    PRIVATE
    page.hpp)
set_target_properties(test_page
    PROPERTIES
    CXX_STANDARD 14)
add_test(
    NAME "memory::test_page"
    COMMAND test_page)
add_tinytest_executable(non_virtual_interface
    non_virtual_interface.cpp)
set_target_properties(non_virtual_interface
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "NVI::non-virtual-interface"
    COMMAND non_virtual_interface)
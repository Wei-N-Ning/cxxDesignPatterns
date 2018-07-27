
add_executable(commandMethods cmdMethods.cc)
set_target_properties(commandMethods
    PROPERTIES
    CXX_STANDARD 14)
add_test(
    NAME "commands::methods"
    COMMAND commandMethods)

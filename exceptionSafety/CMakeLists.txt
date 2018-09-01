
add_executable(exception_safety_guarantees
    exception_safety_guarantees.cpp)
set_target_properties(exception_safety_guarantees
    PROPERTIES
    CXX_STANDARD 14)
add_test(
    NAME
    "exception-safety::assignment-op"
    COMMAND
    exception_safety_guarantees
)
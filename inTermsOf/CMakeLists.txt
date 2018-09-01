
add_executable(implemented_in_terms_of
    implemented_in_terms_of.cpp
)
set_target_properties(implemented_in_terms_of
    PROPERTIES
    CXX_STANDARD 14
)
add_test(
    NAME
    "object-relation::impl-in-terms-of"
    COMMAND
    implemented_in_terms_of
)
#
# common - sharedLibB ----------\
#   |   \                        \
#   |    staticLibA ------------- myLib --- myLibTest
# headerOnlyLibC----------------/
#
# common is a header only library that manages its private global state;
# will this global state remain unique or clash with other copies?

# hol: header only library

add_library(hol_common INTERFACE common.hh)
target_include_directories(hol_common INTERFACE .)

add_library(hol_staticLibA STATIC staticLibA.cpp)
target_link_libraries(hol_staticLibA PRIVATE hol_common)

add_library(hol_sharedLibB SHARED sharedLibB.cpp)
target_link_libraries(hol_sharedLibB PRIVATE hol_common)

add_library(hol_headerOnlyLibC INTERFACE headerOnlyLibC.hh)
target_include_directories(hol_headerOnlyLibC INTERFACE .)
target_link_libraries(hol_headerOnlyLibC INTERFACE hol_common)

add_library(hol_myLib myLib.hh myLib.cpp)
target_include_directories(hol_myLib PUBLIC .)
target_link_libraries(hol_myLib PRIVATE hol_common hol_staticLibA hol_sharedLibB hol_headerOnlyLibC)

add_executable(hol_myLibTest myLibTest.cpp)
target_link_libraries(hol_myLibTest PRIVATE autotimer doctest hol_myLib hol_common)
add_test(NAME "header-only-library::myLibTest" COMMAND hol_myLibTest)
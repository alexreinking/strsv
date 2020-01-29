find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

add_library(test_common OBJECT common.cpp)
target_include_directories(test_common PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_link_libraries(test_common PUBLIC solver_core)

add_subdirectory(correctness)
add_subdirectory(performance)
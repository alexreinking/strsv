cmake_minimum_required(VERSION 3.19)
set(VCPKG_OVERLAY_PORTS "${CMAKE_CURRENT_LIST_DIR}/overlay")
project(strsv VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

enable_testing()
option(BUILD_TESTING "Enable building test code" ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

find_package(Eigen3 REQUIRED)
find_package(OpenBLAS REQUIRED)
find_package(MKL REQUIRED)

add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif ()

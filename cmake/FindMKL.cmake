cmake_minimum_required(VERSION 3.19)

set(MKL_ROOT "$ENV{MKLROOT}" CACHE PATH "Path to MKL root install")

find_path(MKL_INCLUDE
          NAMES mkl_cblas.h
          PATHS "${MKL_ROOT}/include")

find_library(MKL_CORE
             NAMES mkl_core
             PATHS "${MKL_ROOT}/lib/intel64")

find_library(MKL_INTEL_LP64
             NAMES mkl_intel_lp64
             PATHS "${MKL_ROOT}/lib/intel64")

find_library(MKL_SEQUENTIAL
             NAMES mkl_sequential
             PATHS "${MKL_ROOT}/lib/intel64")

mark_as_advanced(
        MKL_INCLUDE
        MKL_CORE
        MKL_INTEL_LP64
        MKL_SEQUENTIAL
)

if (EXISTS "${MKL_INCLUDE}/mkl_version.h")
    file(STRINGS "${MKL_INCLUDE}/mkl_version.h" MKL_VERSION
         REGEX "^#define +__INTEL_MKL"
         ENCODING UTF-8)
    foreach (define IN LISTS MKL_VERSION)
        if (define MATCHES "__INTEL_MKL__ +([0-9]+)$")
            set(MKL_VERSION_MAJOR "${CMAKE_MATCH_1}")
        elseif (define MATCHES "__INTEL_MKL_MINOR__ +([0-9]+)$")
            set(MKL_VERSION_MINOR "${CMAKE_MATCH_1}")
        elseif (define MATCHES "__INTEL_MKL_UPDATE__ +([0-9]+)$")
            set(MKL_VERSION_PATCH "${CMAKE_MATCH_1}")
        endif ()
    endforeach ()
    set(MKL_VERSION "${MKL_VERSION_MAJOR}.${MKL_VERSION_MINOR}.${MKL_VERSION_PATCH}")
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MKL
                                  REQUIRED_VARS MKL_INTEL_LP64 MKL_CORE MKL_SEQUENTIAL MKL_INCLUDE
                                  VERSION_VAR MKL_VERSION
                                  HANDLE_VERSION_RANGE)

if (MKL_FOUND)
    add_library(MKL::core UNKNOWN IMPORTED)
    set_target_properties(MKL::core PROPERTIES IMPORTED_LOCATION "${MKL_CORE}")
    target_link_libraries(MKL::core INTERFACE "${CMAKE_DL_LIBS}")

    add_library(MKL::sequential UNKNOWN IMPORTED)
    set_target_properties(MKL::sequential PROPERTIES IMPORTED_LOCATION  "${MKL_SEQUENTIAL}")
    target_link_libraries(MKL::sequential INTERFACE MKL::core)

    add_library(MKL::64lp_seq UNKNOWN IMPORTED)
    set_target_properties(MKL::64lp_seq PROPERTIES IMPORTED_LOCATION "${MKL_INTEL_LP64}")
    target_link_libraries(MKL::64lp_seq INTERFACE MKL::sequential MKL::core)
    target_compile_definitions(MKL::64lp_seq INTERFACE MKL_ILP64)
    target_include_directories(MKL::64lp_seq INTERFACE "$<BUILD_INTERFACE:${MKL_INCLUDE}>")
endif ()

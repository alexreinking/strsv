add_library(solver_core INTERFACE)
target_include_directories(solver_core INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_link_libraries(solver_core INTERFACE Eigen3::Eigen)

function(add_solver NAME)
    add_library(${NAME} ${ARGN})
    add_library(solvers::${NAME} ALIAS ${NAME})
    target_include_directories(${NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
    target_link_libraries(${NAME} PUBLIC solver_core)
endfunction()

add_subdirectory(solvers)
add_executable(test_correctness_noblas noblas.cpp)
target_link_libraries(test_correctness_noblas
                      PRIVATE
                      test_common
                      solvers::naive
                      solvers::blocked
                      GTest::gtest_main)

add_executable(test_correctness_mkl mkl.cpp)
target_link_libraries(test_correctness_mkl
                      PRIVATE
                      test_common
                      solvers::mkl_solver
                      GTest::gtest_main)

add_executable(test_correctness_openblas openblas.cpp)
target_link_libraries(test_correctness_openblas
                      PRIVATE
                      test_common
                      solvers::openblas_solver
                      solvers::dnc
                      GTest::gtest_main)

gtest_add_tests(TARGET test_correctness_noblas)
gtest_add_tests(TARGET test_correctness_mkl)
gtest_add_tests(TARGET test_correctness_openblas)

add_executable(test_performance_noblas noblas.cpp)
target_link_libraries(test_performance_noblas
                      PRIVATE
                      test_common
                      solvers::naive
                      solvers::blocked
                      benchmark::benchmark)

add_executable(test_performance_mkl mkl.cpp)
target_link_libraries(test_performance_mkl
                      PRIVATE
                      test_common
                      solvers::mkl_solver
                      benchmark::benchmark)

add_executable(test_performance_openblas openblas.cpp)
target_link_libraries(test_performance_openblas
                      PRIVATE
                      test_common
                      solvers::openblas_solver
                      solvers::dnc
                      benchmark::benchmark)

set(test_repetitions 1)

add_test(NAME test_performance_noblas
         COMMAND test_performance_noblas
         --benchmark_out=noblas.csv
         --benchmark_out_format=csv
         --benchmark_counters_tabular=true
         --benchmark_repetitions=${test_repetitions}
         --benchmark_report_aggregates_only=yes)

add_test(NAME test_performance_mkl
         COMMAND test_performance_mkl
         --benchmark_out=mkl.csv
         --benchmark_out_format=csv
         --benchmark_counters_tabular=true
         --benchmark_repetitions=${test_repetitions}
         --benchmark_report_aggregates_only=yes)

add_test(NAME test_performance_openblas
         COMMAND test_performance_openblas
         --benchmark_out=openblas.csv
         --benchmark_out_format=csv
         --benchmark_counters_tabular=true
         --benchmark_repetitions=${test_repetitions}
         --benchmark_report_aggregates_only=yes)

set_tests_properties(
        test_performance_noblas
        test_performance_mkl
        test_performance_openblas
        PROPERTIES
        ENVIRONMENT "OPENBLAS_NUM_THREADS=1;MKL_ENABLE_INSTRUCTIONS=AVX2"
)

add_solver(naive naive.cpp)

add_solver(blocked blocked.cpp)

add_solver(dnc dnc.cpp)
target_link_libraries(dnc PRIVATE OpenBLAS::OpenBLAS)

add_solver(openblas_solver openblas_solver.cpp)
target_link_libraries(openblas_solver PRIVATE OpenBLAS::OpenBLAS)

add_solver(mkl_solver mkl_solver.cpp)
target_link_libraries(mkl_solver PRIVATE MKL::64lp_seq)

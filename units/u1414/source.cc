// u1414 – ceres::(anonymous)::OptionsAreValidForSparseNormalCholesky
// Trích từ internal/ceres/solver.cc, dòng 221–225 (chỉ để xem, không compile)

bool OptionsAreValidForSparseNormalCholesky(const Solver::Options& options,
                                            std::string* error) {
  CHECK_EQ(options.linear_solver_type, SPARSE_NORMAL_CHOLESKY);
  return OptionsAreValidForSparseCholeskyBasedSolver(options, error);
}

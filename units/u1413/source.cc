// u1413 – ceres::(anonymous)::OptionsAreValidForDenseNormalCholesky
// Trích từ internal/ceres/solver.cc, dòng 199–203 (chỉ để xem, không compile)

bool OptionsAreValidForDenseNormalCholesky(const Solver::Options& options,
                                           std::string* error) {
  CHECK_EQ(options.linear_solver_type, DENSE_NORMAL_CHOLESKY);
  return OptionsAreValidForDenseSolver(options, error);
}

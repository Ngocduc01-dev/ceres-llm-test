// u0704 – ceres::internal::DenseCholesky::FactorAndSolve
// Trích từ internal/ceres/dense_cholesky.cc, dòng 136–148 (chỉ để xem, không compile)

LinearSolverTerminationType DenseCholesky::FactorAndSolve(
    int num_cols,
    double* lhs,
    const double* rhs,
    double* solution,
    std::string* message) {
  LinearSolverTerminationType termination_type =
      Factorize(num_cols, lhs, message);
  if (termination_type == LinearSolverTerminationType::SUCCESS) {
    termination_type = Solve(rhs, solution, message);
  }
  return termination_type;
}

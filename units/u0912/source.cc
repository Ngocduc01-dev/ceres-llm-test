// u0912 – ceres::internal::SparseCholesky::FactorAndSolve
// Trích từ internal/ceres/sparse_cholesky.cc, dòng 108–118 (chỉ để xem, không compile)

LinearSolverTerminationType SparseCholesky::FactorAndSolve(
    CompressedRowSparseMatrix* lhs,
    const double* rhs,
    double* solution,
    std::string* message) {
  LinearSolverTerminationType termination_type = Factorize(lhs, message);
  if (termination_type == LinearSolverTerminationType::SUCCESS) {
    termination_type = Solve(rhs, solution, message);
  }
  return termination_type;
}

// u0709 – ceres::internal::DenseQR::FactorAndSolve
// Trích từ internal/ceres/dense_qr.cc, dòng 148–160 (chỉ để xem, không compile)

LinearSolverTerminationType DenseQR::FactorAndSolve(int num_rows,
                                                    int num_cols,
                                                    double* lhs,
                                                    const double* rhs,
                                                    double* solution,
                                                    std::string* message) {
  LinearSolverTerminationType termination_type =
      Factorize(num_rows, num_cols, lhs, message);
  if (termination_type == LinearSolverTerminationType::SUCCESS) {
    termination_type = Solve(rhs, solution, message);
  }
  return termination_type;
}

// u0708 – ceres::internal::FloatEigenDenseCholesky::Solve
// Trích từ internal/ceres/dense_cholesky.cc, dòng 191–203 (chỉ để xem, không compile)

LinearSolverTerminationType FloatEigenDenseCholesky::Solve(
    const double* rhs, double* solution, std::string* message) {
  if (llt_->info() != Eigen::Success) {
    *message = "Eigen failure. Unable to perform dense Cholesky factorization.";
    return LinearSolverTerminationType::FAILURE;
  }

  rhs_ = ConstVectorRef(rhs, llt_->cols()).cast<float>();
  solution_ = llt_->solve(rhs_);
  VectorRef(solution, llt_->cols()) = solution_.cast<double>();
  *message = "Success.";
  return LinearSolverTerminationType::SUCCESS;
}

// u0707 – ceres::internal::FloatEigenDenseCholesky::Factorize
// Trích từ internal/ceres/dense_cholesky.cc, dòng 177–189 (chỉ để xem, không compile)

LinearSolverTerminationType FloatEigenDenseCholesky::Factorize(
    int num_cols, double* lhs, std::string* message) {
  // TODO(sameeragarwal): Check if this causes a double allocation.
  lhs_ = Eigen::Map<Eigen::MatrixXd>(lhs, num_cols, num_cols).cast<float>();
  llt_ = std::make_unique<LLTType>(lhs_);
  if (llt_->info() != Eigen::Success) {
    *message = "Eigen failure. Unable to perform dense Cholesky factorization.";
    return LinearSolverTerminationType::FAILURE;
  }

  *message = "Success.";
  return LinearSolverTerminationType::SUCCESS;
}

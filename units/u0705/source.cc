// u0705 – ceres::internal::EigenDenseCholesky::Factorize
// Trích từ internal/ceres/dense_cholesky.cc, dòng 150–161 (chỉ để xem, không compile)

LinearSolverTerminationType EigenDenseCholesky::Factorize(
    int num_cols, double* lhs, std::string* message) {
  Eigen::Map<Eigen::MatrixXd> m(lhs, num_cols, num_cols);
  llt_ = std::make_unique<LLTType>(m);
  if (llt_->info() != Eigen::Success) {
    *message = "Eigen failure. Unable to perform dense Cholesky factorization.";
    return LinearSolverTerminationType::FAILURE;
  }

  *message = "Success.";
  return LinearSolverTerminationType::SUCCESS;
}

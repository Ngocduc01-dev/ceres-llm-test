// u0657 – ceres::internal::RefinedDenseCholesky::Factorize
// Trích từ internal/ceres/dense_cholesky.cc, dòng 327–332 (chỉ để xem, không compile)

LinearSolverTerminationType RefinedDenseCholesky::Factorize(
    const int num_cols, double* lhs, std::string* message) {
  lhs_ = lhs;
  num_cols_ = num_cols;
  return dense_cholesky_->Factorize(num_cols, lhs, message);
}

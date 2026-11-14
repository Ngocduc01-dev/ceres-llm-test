// u0533 – ceres::internal::VisibilityBasedPreconditioner::RightMultiplyAndAccumulate
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 424–431 (chỉ để xem, không compile)

void VisibilityBasedPreconditioner::RightMultiplyAndAccumulate(
    const double* x, double* y) const {
  CHECK(x != nullptr);
  CHECK(y != nullptr);
  CHECK(sparse_cholesky_ != nullptr);
  std::string message;
  sparse_cholesky_->Solve(x, y, &message);
}

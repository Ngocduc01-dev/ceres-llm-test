// u0513 – ceres::internal::SubsetPreconditioner::RightMultiplyAndAccumulate
// Trích từ internal/ceres/subset_preconditioner.cc, dòng 60–66 (chỉ để xem, không compile)

void SubsetPreconditioner::RightMultiplyAndAccumulate(const double* x,
                                                      double* y) const {
  CHECK(x != nullptr);
  CHECK(y != nullptr);
  std::string message;
  sparse_cholesky_->Solve(x, y, &message);
}

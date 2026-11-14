// u1107 – ceres::NormalPrior::NormalPrior
// Trích từ internal/ceres/normal_prior.cc, dòng 43–49 (chỉ để xem, không compile)

NormalPrior::NormalPrior(const Matrix& A, Vector b) : A_(A), b_(std::move(b)) {
  CHECK_GT(b_.rows(), 0);
  CHECK_GT(A_.rows(), 0);
  CHECK_EQ(b_.rows(), A.cols());
  set_num_residuals(A_.rows());
  mutable_parameter_block_sizes()->push_back(b_.rows());
}

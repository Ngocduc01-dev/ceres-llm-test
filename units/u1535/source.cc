// u1535 – ceres::Covariance::Compute
// Trích từ internal/ceres/covariance.cc, dòng 48–53 (chỉ để xem, không compile)

bool Covariance::Compute(
    const std::vector<std::pair<const double*, const double*>>&
        covariance_blocks,
    Problem* problem) {
  return impl_->Compute(covariance_blocks, problem->mutable_impl());
}

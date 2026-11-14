// u1540 – ceres::Covariance::Compute
// Trích từ internal/ceres/covariance.cc, dòng 55–58 (chỉ để xem, không compile)

bool Covariance::Compute(const std::vector<const double*>& parameter_blocks,
                         Problem* problem) {
  return impl_->Compute(parameter_blocks, problem->mutable_impl());
}

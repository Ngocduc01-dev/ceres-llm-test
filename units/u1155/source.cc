// u1155 – ceres::Problem::HasParameterBlock
// Trích từ internal/ceres/problem.cc, dòng 179–181 (chỉ để xem, không compile)

bool Problem::HasParameterBlock(const double* values) const {
  return impl_->HasParameterBlock(values);
}

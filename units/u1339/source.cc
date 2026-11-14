// u1339 – ceres::Problem::ParameterBlockTangentSize
// Trích từ internal/ceres/problem.cc, dòng 175–177 (chỉ để xem, không compile)

int Problem::ParameterBlockTangentSize(const double* values) const {
  return impl_->ParameterBlockTangentSize(values);
}

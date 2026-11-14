// u1428 – ceres::Problem::IsParameterBlockConstant
// Trích từ internal/ceres/problem.cc, dòng 92–94 (chỉ để xem, không compile)

bool Problem::IsParameterBlockConstant(const double* values) const {
  return impl_->IsParameterBlockConstant(values);
}

// u1338 – ceres::Problem::ParameterBlockSize
// Trích từ internal/ceres/problem.cc, dòng 171–173 (chỉ để xem, không compile)

int Problem::ParameterBlockSize(const double* values) const {
  return impl_->ParameterBlockSize(values);
}

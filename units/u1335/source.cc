// u1335 – ceres::Problem::GetParameterLowerBound
// Trích từ internal/ceres/problem.cc, dòng 124–126 (chỉ để xem, không compile)

double Problem::GetParameterLowerBound(const double* values, int index) const {
  return impl_->GetParameterLowerBound(values, index);
}

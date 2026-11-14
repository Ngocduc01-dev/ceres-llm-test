// u1334 – ceres::Problem::GetParameterUpperBound
// Trích từ internal/ceres/problem.cc, dòng 120–122 (chỉ để xem, không compile)

double Problem::GetParameterUpperBound(const double* values, int index) const {
  return impl_->GetParameterUpperBound(values, index);
}

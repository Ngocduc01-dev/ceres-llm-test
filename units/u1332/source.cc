// u1332 – ceres::Problem::SetParameterLowerBound
// Trích từ internal/ceres/problem.cc, dòng 108–112 (chỉ để xem, không compile)

void Problem::SetParameterLowerBound(double* values,
                                     int index,
                                     double lower_bound) {
  impl_->SetParameterLowerBound(values, index, lower_bound);
}

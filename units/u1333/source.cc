// u1333 – ceres::Problem::SetParameterUpperBound
// Trích từ internal/ceres/problem.cc, dòng 114–118 (chỉ để xem, không compile)

void Problem::SetParameterUpperBound(double* values,
                                     int index,
                                     double upper_bound) {
  impl_->SetParameterUpperBound(values, index, upper_bound);
}

// u1329 – ceres::Problem::SetParameterBlockConstant
// Trích từ internal/ceres/problem.cc, dòng 84–86 (chỉ để xem, không compile)

void Problem::SetParameterBlockConstant(const double* values) {
  impl_->SetParameterBlockConstant(values);
}

// u1525 – ceres::Problem::AddParameterBlock
// Trích từ internal/ceres/problem.cc, dòng 68–70 (chỉ để xem, không compile)

void Problem::AddParameterBlock(double* values, int size) {
  impl_->AddParameterBlock(values, size);
}

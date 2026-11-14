// u1528 – ceres::Problem::RemoveParameterBlock
// Trích từ internal/ceres/problem.cc, dòng 80–82 (chỉ để xem, không compile)

void Problem::RemoveParameterBlock(const double* values) {
  impl_->RemoveParameterBlock(values);
}

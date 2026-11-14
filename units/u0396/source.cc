// u0396 – ceres::internal::Program::mutable_residual_blocks
// Trích từ internal/ceres/program.cc, dòng 69–71 (chỉ để xem, không compile)

std::vector<ResidualBlock*>* Program::mutable_residual_blocks() {
  return &residual_blocks_;
}

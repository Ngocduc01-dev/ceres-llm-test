// u1262 – ceres::internal::Program::MaxResidualsPerResidualBlock
// Trích từ internal/ceres/program.cc, dòng 544–550 (chỉ để xem, không compile)

int Program::MaxResidualsPerResidualBlock() const {
  int max_residuals = 0;
  for (auto* residual_block : residual_blocks_) {
    max_residuals = std::max(max_residuals, residual_block->NumResiduals());
  }
  return max_residuals;
}

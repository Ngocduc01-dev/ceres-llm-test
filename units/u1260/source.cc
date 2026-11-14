// u1260 – ceres::internal::Program::NumResiduals
// Trích từ internal/ceres/program.cc, dòng 483–489 (chỉ để xem, không compile)

int Program::NumResiduals() const {
  int num_residuals = 0;
  for (auto* residual_block : residual_blocks_) {
    num_residuals += residual_block->NumResiduals();
  }
  return num_residuals;
}

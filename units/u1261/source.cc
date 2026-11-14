// u1261 – ceres::internal::Program::MaxParametersPerResidualBlock
// Trích từ internal/ceres/program.cc, dòng 535–542 (chỉ để xem, không compile)

int Program::MaxParametersPerResidualBlock() const {
  int max_parameters = 0;
  for (auto* residual_block : residual_blocks_) {
    max_parameters =
        std::max(max_parameters, residual_block->NumParameterBlocks());
  }
  return max_parameters;
}

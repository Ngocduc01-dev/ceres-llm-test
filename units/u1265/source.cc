// u1265 – ceres::internal::Program::MaxDerivativesPerResidualBlock
// Trích từ internal/ceres/program.cc, dòng 521–533 (chỉ để xem, không compile)

int Program::MaxDerivativesPerResidualBlock() const {
  int max_derivatives = 0;
  for (auto* residual_block : residual_blocks_) {
    int derivatives = 0;
    int num_parameters = residual_block->NumParameterBlocks();
    for (int j = 0; j < num_parameters; ++j) {
      derivatives += residual_block->NumResiduals() *
                     residual_block->parameter_blocks()[j]->TangentSize();
    }
    max_derivatives = std::max(max_derivatives, derivatives);
  }
  return max_derivatives;
}

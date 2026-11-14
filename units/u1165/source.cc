// u1165 – ceres::internal::ResidualBlock::ResidualBlock
// Trích từ internal/ceres/residual_block.cc, dòng 52–66 (chỉ để xem, không compile)

ResidualBlock::ResidualBlock(
    const CostFunction* cost_function,
    const LossFunction* loss_function,
    const std::vector<ParameterBlock*>& parameter_blocks,
    int index)
    : cost_function_(cost_function),
      loss_function_(loss_function),
      parameter_blocks_(
          new ParameterBlock*[cost_function->parameter_block_sizes().size()]),
      index_(index) {
  CHECK(cost_function_ != nullptr);
  std::copy(parameter_blocks.begin(),
            parameter_blocks.end(),
            parameter_blocks_.get());
}

// u1020 – ceres::internal::ResidualBlock::NumParameterBlocks
// Trích từ internal/ceres/residual_block.h, dòng 119–121 (chỉ để xem, không compile)

  int NumParameterBlocks() const {
    return cost_function_->parameter_block_sizes().size();
  }

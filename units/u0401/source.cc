// u0401 – ceres::internal::ResidualBlock::parameter_blocks
// Trích từ internal/ceres/residual_block.h, dòng 114–116 (chỉ để xem, không compile)

  ParameterBlock* const* parameter_blocks() const {
    return parameter_blocks_.get();
  }

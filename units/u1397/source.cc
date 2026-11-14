// u1397 – ceres::internal::ParameterBlock::AddResidualBlock
// Trích từ internal/ceres/parameter_block.h, dòng 275–280 (chỉ để xem, không compile)

  void AddResidualBlock(ResidualBlock* residual_block) {
    CHECK(residual_blocks_.get() != nullptr)
        << "Ceres bug: The residual block collection is null for parameter "
        << "block: " << ToString();
    residual_blocks_->insert(residual_block);
  }

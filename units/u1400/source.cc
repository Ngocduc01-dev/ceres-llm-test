// u1400 – ceres::internal::ParameterBlock::RemoveResidualBlock
// Trích từ internal/ceres/parameter_block.h, dòng 282–289 (chỉ để xem, không compile)

  void RemoveResidualBlock(ResidualBlock* residual_block) {
    CHECK(residual_blocks_.get() != nullptr)
        << "Ceres bug: The residual block collection is null for parameter "
        << "block: " << ToString();
    CHECK(residual_blocks_->find(residual_block) != residual_blocks_->end())
        << "Ceres bug: Missing residual for parameter block: " << ToString();
    residual_blocks_->erase(residual_block);
  }

// u1384 – ceres::internal::ParameterBlock::EnableResidualBlockDependencies
// Trích từ internal/ceres/parameter_block.h, dòng 268–273 (chỉ để xem, không compile)

  void EnableResidualBlockDependencies() {
    CHECK(residual_blocks_.get() == nullptr)
        << "Ceres bug: There is already a residual block collection "
        << "for parameter block: " << ToString();
    residual_blocks_ = std::make_unique<ResidualBlockSet>();
  }

// u1342 – ceres::Problem::GetLossFunctionForResidualBlock
// Trích từ internal/ceres/problem.cc, dòng 203–206 (chỉ để xem, không compile)

const LossFunction* Problem::GetLossFunctionForResidualBlock(
    const ResidualBlockId residual_block) const {
  return impl_->GetLossFunctionForResidualBlock(residual_block);
}

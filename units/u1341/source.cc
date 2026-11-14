// u1341 – ceres::Problem::GetCostFunctionForResidualBlock
// Trích từ internal/ceres/problem.cc, dòng 198–201 (chỉ để xem, không compile)

const CostFunction* Problem::GetCostFunctionForResidualBlock(
    const ResidualBlockId residual_block) const {
  return impl_->GetCostFunctionForResidualBlock(residual_block);
}

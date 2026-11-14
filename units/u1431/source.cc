// u1431 – ceres::Problem::GetParameterBlocksForResidualBlock
// Trích từ internal/ceres/problem.cc, dòng 192–196 (chỉ để xem, không compile)

void Problem::GetParameterBlocksForResidualBlock(
    const ResidualBlockId residual_block,
    std::vector<double*>* parameter_blocks) const {
  impl_->GetParameterBlocksForResidualBlock(residual_block, parameter_blocks);
}

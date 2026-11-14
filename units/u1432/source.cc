// u1432 – ceres::Problem::GetResidualBlocksForParameterBlock
// Trích từ internal/ceres/problem.cc, dòng 208–211 (chỉ để xem, không compile)

void Problem::GetResidualBlocksForParameterBlock(
    const double* values, std::vector<ResidualBlockId>* residual_blocks) const {
  impl_->GetResidualBlocksForParameterBlock(values, residual_blocks);
}

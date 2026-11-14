// u1340 – ceres::Problem::GetResidualBlocks
// Trích từ internal/ceres/problem.cc, dòng 187–190 (chỉ để xem, không compile)

void Problem::GetResidualBlocks(
    std::vector<ResidualBlockId>* residual_blocks) const {
  impl_->GetResidualBlocks(residual_blocks);
}

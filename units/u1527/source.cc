// u1527 – ceres::Problem::RemoveResidualBlock
// Trích từ internal/ceres/problem.cc, dòng 76–78 (chỉ để xem, không compile)

void Problem::RemoveResidualBlock(ResidualBlockId residual_block) {
  impl_->RemoveResidualBlock(residual_block);
}

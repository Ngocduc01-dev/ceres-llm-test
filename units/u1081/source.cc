// u1081 – ceres::internal::ReorderResidualBlocksByPartition
// Trích từ internal/ceres/reorder_program.cc, dòng 597–607 (chỉ để xem, không compile)

int ReorderResidualBlocksByPartition(
    const std::unordered_set<ResidualBlockId>& bottom_residual_blocks,
    Program* program) {
  auto residual_blocks = program->mutable_residual_blocks();
  auto it = std::partition(residual_blocks->begin(),
                           residual_blocks->end(),
                           [&bottom_residual_blocks](ResidualBlock* r) {
                             return bottom_residual_blocks.count(r) == 0;
                           });
  return it - residual_blocks->begin();
}

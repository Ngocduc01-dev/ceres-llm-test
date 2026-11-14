// u1477 – ceres::internal::ProblemImpl::InternalRemoveResidualBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 176–194 (chỉ để xem, không compile)

void ProblemImpl::InternalRemoveResidualBlock(ResidualBlock* residual_block) {
  CHECK(residual_block != nullptr);
  // Perform no check on the validity of residual_block, that is handled in
  // the public method: RemoveResidualBlock().

  // If needed, remove the parameter dependencies on this residual block.
  if (options_.enable_fast_removal) {
    const int num_parameter_blocks_for_residual =
        residual_block->NumParameterBlocks();
    for (int i = 0; i < num_parameter_blocks_for_residual; ++i) {
      residual_block->parameter_blocks()[i]->RemoveResidualBlock(
          residual_block);
    }

    auto it = residual_block_set_.find(residual_block);
    residual_block_set_.erase(it);
  }
  DeleteBlockInVector(program_->mutable_residual_blocks(), residual_block);
}

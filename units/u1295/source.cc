// u1295 – ceres::internal::Program::IsParameterBlockSetIndependent
// Trích từ internal/ceres/program.cc, dòng 413–432 (chỉ để xem, không compile)

bool Program::IsParameterBlockSetIndependent(
    const std::set<double*>& independent_set) const {
  // Loop over each residual block and ensure that no two parameter
  // blocks in the same residual block are part of
  // parameter_block_ptrs as that would violate the assumption that it
  // is an independent set in the Hessian matrix.
  for (const ResidualBlock* residual_block : residual_blocks_) {
    ParameterBlock* const* parameter_blocks =
        residual_block->parameter_blocks();
    const int num_parameter_blocks = residual_block->NumParameterBlocks();
    int count = 0;
    for (int i = 0; i < num_parameter_blocks; ++i) {
      count += independent_set.count(parameter_blocks[i]->mutable_user_state());
    }
    if (count > 1) {
      return false;
    }
  }
  return true;
}

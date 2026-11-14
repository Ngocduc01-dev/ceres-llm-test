// u1499 – ceres::internal::ProblemImpl::RemoveParameterBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 435–471 (chỉ để xem, không compile)

void ProblemImpl::RemoveParameterBlock(const double* values) {
  ParameterBlock* parameter_block = FindWithDefault(
      parameter_block_map_, const_cast<double*>(values), nullptr);
  if (parameter_block == nullptr) {
    LOG(FATAL) << "Parameter block not found: " << values
               << ". You must add the parameter block to the problem before "
               << "it can be removed.";
  }

  if (options_.enable_fast_removal) {
    // Copy the dependent residuals from the parameter block because the set of
    // dependents will change after each call to RemoveResidualBlock().
    std::vector<ResidualBlock*> residual_blocks_to_remove(
        parameter_block->mutable_residual_blocks()->begin(),
        parameter_block->mutable_residual_blocks()->end());
    for (auto* residual_block : residual_blocks_to_remove) {
      InternalRemoveResidualBlock(residual_block);
    }
  } else {
    // Scan all the residual blocks to remove ones that depend on the parameter
    // block. Do the scan backwards since the vector changes while iterating.
    const int num_residual_blocks = NumResidualBlocks();
    for (int i = num_residual_blocks - 1; i >= 0; --i) {
      ResidualBlock* residual_block =
          (*(program_->mutable_residual_blocks()))[i];
      const int num_parameter_blocks = residual_block->NumParameterBlocks();
      for (int j = 0; j < num_parameter_blocks; ++j) {
        if (residual_block->parameter_blocks()[j] == parameter_block) {
          InternalRemoveResidualBlock(residual_block);
          // The parameter blocks are guaranteed unique.
          break;
        }
      }
    }
  }
  DeleteBlockInVector(program_->mutable_parameter_blocks(), parameter_block);
}

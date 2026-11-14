// u1302 – ceres::internal::ProblemImpl::GetResidualBlocksForParameterBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 865–901 (chỉ để xem, không compile)

void ProblemImpl::GetResidualBlocksForParameterBlock(
    const double* values, std::vector<ResidualBlockId>* residual_blocks) const {
  ParameterBlock* parameter_block = FindWithDefault(
      parameter_block_map_, const_cast<double*>(values), nullptr);
  if (parameter_block == nullptr) {
    LOG(FATAL) << "Parameter block not found: " << values
               << ". You must add the parameter block to the problem before "
               << "you can get the residual blocks that depend on it.";
  }

  if (options_.enable_fast_removal) {
    // In this case the residual blocks that depend on the parameter block are
    // stored in the parameter block already, so just copy them out.
    CHECK(residual_blocks != nullptr);
    residual_blocks->resize(parameter_block->mutable_residual_blocks()->size());
    std::copy(parameter_block->mutable_residual_blocks()->begin(),
              parameter_block->mutable_residual_blocks()->end(),
              residual_blocks->begin());
    return;
  }

  // Find residual blocks that depend on the parameter block.
  CHECK(residual_blocks != nullptr);
  residual_blocks->clear();
  const int num_residual_blocks = NumResidualBlocks();
  for (int i = 0; i < num_residual_blocks; ++i) {
    ResidualBlock* residual_block = (*(program_->mutable_residual_blocks()))[i];
    const int num_parameter_blocks = residual_block->NumParameterBlocks();
    for (int j = 0; j < num_parameter_blocks; ++j) {
      if (residual_block->parameter_blocks()[j] == parameter_block) {
        residual_blocks->push_back(residual_block);
        // The parameter blocks are guaranteed unique.
        break;
      }
    }
  }
}

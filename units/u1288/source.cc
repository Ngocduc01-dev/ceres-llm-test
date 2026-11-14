// u1288 – ceres::internal::ProblemImpl::GetParameterBlocksForResidualBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 843–853 (chỉ để xem, không compile)

void ProblemImpl::GetParameterBlocksForResidualBlock(
    const ResidualBlockId residual_block,
    std::vector<double*>* parameter_blocks) const {
  int num_parameter_blocks = residual_block->NumParameterBlocks();
  CHECK(parameter_blocks != nullptr);
  parameter_blocks->resize(num_parameter_blocks);
  for (int i = 0; i < num_parameter_blocks; ++i) {
    (*parameter_blocks)[i] =
        residual_block->parameter_blocks()[i]->mutable_user_state();
  }
}

// u1311 – ceres::internal::(anonymous)::MinParameterBlock
// Trích từ internal/ceres/reorder_program.cc, dòng 76–90 (chỉ để xem, không compile)

static int MinParameterBlock(const ResidualBlock* residual_block,
                             int size_of_first_elimination_group) {
  int min_parameter_block_position = size_of_first_elimination_group;
  for (int i = 0; i < residual_block->NumParameterBlocks(); ++i) {
    ParameterBlock* parameter_block = residual_block->parameter_blocks()[i];
    if (!parameter_block->IsConstant()) {
      CHECK_NE(parameter_block->index(), -1)
          << "Did you forget to call Program::SetParameterOffsetsAndIndex()? "
          << "This is a Ceres bug; please contact the developers!";
      min_parameter_block_position =
          std::min(parameter_block->index(), min_parameter_block_position);
    }
  }
  return min_parameter_block_position;
}

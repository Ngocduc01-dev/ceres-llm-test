// u1287 – ceres::internal::CompressedRowJacobianWriter::GetOrderedParameterBlocks
// Trích từ internal/ceres/compressed_row_jacobian_writer.cc, dòng 71–87 (chỉ để xem, không compile)

void CompressedRowJacobianWriter::GetOrderedParameterBlocks(
    const Program* program,
    int residual_id,
    std::vector<std::pair<int, int>>* evaluated_jacobian_blocks) {
  auto residual_block = program->residual_blocks()[residual_id];
  const int num_parameter_blocks = residual_block->NumParameterBlocks();

  for (int j = 0; j < num_parameter_blocks; ++j) {
    auto parameter_block = residual_block->parameter_blocks()[j];
    if (!parameter_block->IsConstant()) {
      evaluated_jacobian_blocks->push_back(
          std::make_pair(parameter_block->index(), j));
    }
  }
  std::sort(evaluated_jacobian_blocks->begin(),
            evaluated_jacobian_blocks->end());
}

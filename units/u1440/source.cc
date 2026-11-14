// u1440 – ceres::internal::DynamicCompressedRowJacobianWriter::Write
// Trích từ internal/ceres/dynamic_compressed_row_jacobian_writer.cc, dòng 59–99 (chỉ để xem, không compile)

void DynamicCompressedRowJacobianWriter::Write(int residual_id,
                                               int residual_offset,
                                               double** jacobians,
                                               SparseMatrix* base_jacobian) {
  auto* jacobian = down_cast<DynamicCompressedRowSparseMatrix*>(base_jacobian);

  // Get the `residual_block` of interest.
  const ResidualBlock* residual_block =
      program_->residual_blocks()[residual_id];
  const int num_residuals = residual_block->NumResiduals();

  std::vector<std::pair<int, int>> evaluated_jacobian_blocks;
  CompressedRowJacobianWriter::GetOrderedParameterBlocks(
      program_, residual_id, &evaluated_jacobian_blocks);

  // `residual_offset` is the residual row in the global jacobian.
  // Empty the jacobian rows.
  jacobian->ClearRows(residual_offset, num_residuals);

  // Iterate over each parameter block.
  for (const auto& evaluated_jacobian_block : evaluated_jacobian_blocks) {
    const ParameterBlock* parameter_block =
        program_->parameter_blocks()[evaluated_jacobian_block.first];
    const int parameter_block_jacobian_index = evaluated_jacobian_block.second;
    const int parameter_block_size = parameter_block->TangentSize();
    const double* parameter_jacobian =
        jacobians[parameter_block_jacobian_index];

    // For each parameter block only insert its non-zero entries.
    for (int r = 0; r < num_residuals; ++r) {
      for (int c = 0; c < parameter_block_size; ++c, ++parameter_jacobian) {
        const double v = *parameter_jacobian;
        // Only insert non-zero entries.
        if (v != 0.0) {
          jacobian->InsertEntry(
              residual_offset + r, parameter_block->delta_offset() + c, v);
        }
      }
    }
  }
}

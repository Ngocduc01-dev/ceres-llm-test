// u1437 – ceres::internal::CompressedRowJacobianWriter::Write
// Trích từ internal/ceres/compressed_row_jacobian_writer.cc, dòng 201–244 (chỉ để xem, không compile)

void CompressedRowJacobianWriter::Write(int residual_id,
                                        int residual_offset,
                                        double** jacobians,
                                        SparseMatrix* base_jacobian) {
  auto* jacobian = down_cast<CompressedRowSparseMatrix*>(base_jacobian);

  double* jacobian_values = jacobian->mutable_values();
  const int* jacobian_rows = jacobian->rows();

  auto residual_block = program_->residual_blocks()[residual_id];
  const int num_residuals = residual_block->NumResiduals();

  std::vector<std::pair<int, int>> evaluated_jacobian_blocks;
  GetOrderedParameterBlocks(program_, residual_id, &evaluated_jacobian_blocks);

  // Where in the current row does the jacobian for a parameter block begin.
  int col_pos = 0;

  // Iterate over the jacobian blocks in increasing order of their
  // positions in the reduced parameter vector.
  for (auto& evaluated_jacobian_block : evaluated_jacobian_blocks) {
    auto parameter_block =
        program_->parameter_blocks()[evaluated_jacobian_block.first];
    const int argument = evaluated_jacobian_block.second;
    const int parameter_block_size = parameter_block->TangentSize();

    // Copy one row of the jacobian block at a time.
    for (int r = 0; r < num_residuals; ++r) {
      // Position of the r^th row of the current jacobian block.
      const double* block_row_begin =
          jacobians[argument] + r * parameter_block_size;

      // Position in the values array of the jacobian where this
      // row of the jacobian block should go.
      double* column_block_begin =
          jacobian_values + jacobian_rows[residual_offset + r] + col_pos;

      std::copy(block_row_begin,
                block_row_begin + parameter_block_size,
                column_block_begin);
    }
    col_pos += parameter_block_size;
  }
}

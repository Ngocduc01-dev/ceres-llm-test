// u1368 – ceres::internal::BlockJacobianWriter::CreateJacobian
// Trích từ internal/ceres/block_jacobian_writer.cc, dòng 196–261 (chỉ để xem, không compile)

std::unique_ptr<SparseMatrix> BlockJacobianWriter::CreateJacobian() const {
  if (!jacobian_layout_is_valid_) {
    LOG(ERROR) << "Unable to create Jacobian matrix. Too many entries in the "
                  "Jacobian matrix.";
    return nullptr;
  }

  auto* bs = new CompressedRowBlockStructure;

  const std::vector<ParameterBlock*>& parameter_blocks =
      program_->parameter_blocks();

  // Construct the column blocks.
  bs->cols.resize(parameter_blocks.size());
  for (int i = 0, cursor = 0; i < parameter_blocks.size(); ++i) {
    CHECK_NE(parameter_blocks[i]->index(), -1);
    CHECK(!parameter_blocks[i]->IsConstant());
    bs->cols[i].size = parameter_blocks[i]->TangentSize();
    bs->cols[i].position = cursor;
    cursor += bs->cols[i].size;
  }

  // Construct the cells in each row.
  const std::vector<ResidualBlock*>& residual_blocks =
      program_->residual_blocks();
  int row_block_position = 0;
  bs->rows.resize(residual_blocks.size());
  for (int i = 0; i < residual_blocks.size(); ++i) {
    const ResidualBlock* residual_block = residual_blocks[i];
    CompressedRow* row = &bs->rows[i];

    row->block.size = residual_block->NumResiduals();
    row->block.position = row_block_position;
    row_block_position += row->block.size;

    // Size the row by the number of active parameters in this residual.
    const int num_parameter_blocks = residual_block->NumParameterBlocks();
    int num_active_parameter_blocks = 0;
    for (int j = 0; j < num_parameter_blocks; ++j) {
      if (residual_block->parameter_blocks()[j]->index() != -1) {
        num_active_parameter_blocks++;
      }
    }
    row->cells.resize(num_active_parameter_blocks);

    // Add layout information for the active parameters in this row.
    for (int j = 0, k = 0; j < num_parameter_blocks; ++j) {
      const ParameterBlock* parameter_block =
          residual_block->parameter_blocks()[j];
      if (!parameter_block->IsConstant()) {
        Cell& cell = row->cells[k];
        cell.block_id = parameter_block->index();
        cell.position = jacobian_layout_[i][k];

        // Only increment k for active parameters, since there is only layout
        // information for active parameters.
        k++;
      }
    }

    std::sort(row->cells.begin(), row->cells.end(), CellLessThan);
  }

  return std::make_unique<BlockSparseMatrix>(
      bs, options_.sparse_linear_algebra_library_type == CUDA_SPARSE);
}

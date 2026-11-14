// u1445 – ceres::internal::CompressedRowJacobianWriter::CreateJacobian
// Trích từ internal/ceres/compressed_row_jacobian_writer.cc, dòng 89–199 (chỉ để xem, không compile)

std::unique_ptr<SparseMatrix> CompressedRowJacobianWriter::CreateJacobian()
    const {
  const auto& residual_blocks = program_->residual_blocks();

  const int total_num_residuals = program_->NumResiduals();
  const int total_num_effective_parameters = program_->NumEffectiveParameters();

  // Count the number of jacobian nonzeros.
  //
  // We used an unsigned int here, so that we can compare it INT_MAX without
  // triggering overflow behaviour.
  unsigned int num_jacobian_nonzeros = total_num_effective_parameters;
  for (auto* residual_block : residual_blocks) {
    const int num_residuals = residual_block->NumResiduals();
    const int num_parameter_blocks = residual_block->NumParameterBlocks();
    for (int j = 0; j < num_parameter_blocks; ++j) {
      auto parameter_block = residual_block->parameter_blocks()[j];
      if (!parameter_block->IsConstant()) {
        num_jacobian_nonzeros += num_residuals * parameter_block->TangentSize();
        if (num_jacobian_nonzeros > std::numeric_limits<int>::max()) {
          LOG(ERROR) << "Unable to create Jacobian matrix: Too many entries in "
                        "the Jacobian matrix. num_jacobian_nonzeros = "
                     << num_jacobian_nonzeros;
          return nullptr;
        }
      }
    }
  }

  // Allocate storage for the jacobian with some extra space at the end.
  // Allocate more space than needed to store the jacobian so that when the LM
  // algorithm adds the diagonal, no reallocation is necessary. This reduces
  // peak memory usage significantly.
  auto jacobian = std::make_unique<CompressedRowSparseMatrix>(
      total_num_residuals,
      total_num_effective_parameters,
      static_cast<int>(num_jacobian_nonzeros));

  // At this stage, the CompressedRowSparseMatrix is an invalid state. But
  // this seems to be the only way to construct it without doing a memory
  // copy.
  int* rows = jacobian->mutable_rows();
  int* cols = jacobian->mutable_cols();

  int row_pos = 0;
  rows[0] = 0;
  for (auto* residual_block : residual_blocks) {
    const int num_parameter_blocks = residual_block->NumParameterBlocks();

    // Count the number of derivatives for a row of this residual block and
    // build a list of active parameter block indices.
    int num_derivatives = 0;
    std::vector<int> parameter_indices;
    for (int j = 0; j < num_parameter_blocks; ++j) {
      auto parameter_block = residual_block->parameter_blocks()[j];
      if (!parameter_block->IsConstant()) {
        parameter_indices.push_back(parameter_block->index());
        num_derivatives += parameter_block->TangentSize();
      }
    }

    // Sort the parameters by their position in the state vector.
    std::sort(parameter_indices.begin(), parameter_indices.end());
    if (adjacent_find(parameter_indices.begin(), parameter_indices.end()) !=
        parameter_indices.end()) {
      std::string parameter_block_description;
      for (int j = 0; j < num_parameter_blocks; ++j) {
        auto parameter_block = residual_block->parameter_blocks()[j];
        parameter_block_description += parameter_block->ToString() + "\n";
      }
      LOG(FATAL) << "Ceres internal error: "
                 << "Duplicate parameter blocks detected in a cost function. "
                 << "This should never happen. Please report this to "
                 << "the Ceres developers.\n"
                 << "Residual Block: " << residual_block->ToString() << "\n"
                 << "Parameter Blocks: " << parameter_block_description;
    }

    // Update the row indices.
    const int num_residuals = residual_block->NumResiduals();
    for (int j = 0; j < num_residuals; ++j) {
      rows[row_pos + j + 1] = rows[row_pos + j] + num_derivatives;
    }

    // Iterate over parameter blocks in the order which they occur in the
    // parameter vector. This code mirrors that in Write(), where jacobian
    // values are updated.
    int col_pos = 0;
    for (int parameter_index : parameter_indices) {
      auto parameter_block = program_->parameter_blocks()[parameter_index];
      const int parameter_block_size = parameter_block->TangentSize();

      for (int r = 0; r < num_residuals; ++r) {
        // This is the position in the values array of the jacobian where this
        // row of the jacobian block should go.
        const int column_block_begin = rows[row_pos + r] + col_pos;
        for (int c = 0; c < parameter_block_size; ++c) {
          cols[column_block_begin + c] = parameter_block->delta_offset() + c;
        }
      }
      col_pos += parameter_block_size;
    }
    row_pos += num_residuals;
  }
  CHECK_EQ(num_jacobian_nonzeros - total_num_effective_parameters,
           rows[total_num_residuals]);

  PopulateJacobianRowAndColumnBlockVectors(program_, jacobian.get());

  return jacobian;
}

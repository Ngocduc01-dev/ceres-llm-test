// u1317 – ceres::internal::(anonymous)::BuildJacobianLayout
// Trích từ internal/ceres/block_jacobian_writer.cc, dòng 66–165 (chỉ để xem, không compile)

bool BuildJacobianLayout(const Program& program,
                         int num_eliminate_blocks,
                         std::vector<int*>* jacobian_layout,
                         std::vector<int>* jacobian_layout_storage) {
  const std::vector<ResidualBlock*>& residual_blocks =
      program.residual_blocks();

  // Iterate over all the active residual blocks and determine how many E blocks
  // are there. This will determine where the F blocks start in the jacobian
  // matrix. Also compute the number of jacobian blocks.
  unsigned int f_block_pos = 0;
  unsigned int num_jacobian_blocks = 0;
  for (auto* residual_block : residual_blocks) {
    const int num_residuals = residual_block->NumResiduals();
    const int num_parameter_blocks = residual_block->NumParameterBlocks();

    // Advance f_block_pos over each E block for this residual.
    for (int j = 0; j < num_parameter_blocks; ++j) {
      ParameterBlock* parameter_block = residual_block->parameter_blocks()[j];
      if (!parameter_block->IsConstant()) {
        // Only count blocks for active parameters.
        num_jacobian_blocks++;
        if (parameter_block->index() < num_eliminate_blocks) {
          f_block_pos += num_residuals * parameter_block->TangentSize();
        }
      }
    }
    if (num_jacobian_blocks > std::numeric_limits<int>::max()) {
      LOG(ERROR) << "Overlow error. Too many blocks in the jacobian matrix : "
                 << num_jacobian_blocks;
      return false;
    }
  }

  // We now know that the E blocks are laid out starting at zero, and the F
  // blocks are laid out starting at f_block_pos. Iterate over the residual
  // blocks again, and this time fill the jacobian_layout array with the
  // position information.

  jacobian_layout->resize(program.NumResidualBlocks());
  jacobian_layout_storage->resize(num_jacobian_blocks);

  int e_block_pos = 0;
  int* jacobian_pos = jacobian_layout_storage->data();
  std::vector<std::pair<int, int>> active_parameter_blocks;
  for (int i = 0; i < residual_blocks.size(); ++i) {
    const ResidualBlock* residual_block = residual_blocks[i];
    const int num_residuals = residual_block->NumResiduals();
    const int num_parameter_blocks = residual_block->NumParameterBlocks();

    (*jacobian_layout)[i] = jacobian_pos;
    // Cells from F sub-matrix are to be stored sequentially with increasing
    // column block id. For each non-constant parameter block, a pair of indices
    // (index in the list of active parameter blocks and index in the list of
    // all parameter blocks) is computed, and index pairs are sorted by the
    // index of corresponding column block id.
    active_parameter_blocks.clear();
    active_parameter_blocks.reserve(num_parameter_blocks);
    for (int j = 0; j < num_parameter_blocks; ++j) {
      ParameterBlock* parameter_block = residual_block->parameter_blocks()[j];
      if (parameter_block->IsConstant()) {
        continue;
      }
      const int k = active_parameter_blocks.size();
      active_parameter_blocks.emplace_back(k, j);
    }
    std::sort(active_parameter_blocks.begin(),
              active_parameter_blocks.end(),
              [&residual_block](const std::pair<int, int>& a,
                                const std::pair<int, int>& b) {
                return residual_block->parameter_blocks()[a.second]->index() <
                       residual_block->parameter_blocks()[b.second]->index();
              });
    // Cell positions for each active parameter block are filled in the order of
    // active parameter block indices sorted by columnd block index. This
    // guarantees that cells are laid out sequentially with increasing column
    // block indices.
    for (const auto& indices : active_parameter_blocks) {
      const auto [k, j] = indices;
      ParameterBlock* parameter_block = residual_block->parameter_blocks()[j];
      const int parameter_block_index = parameter_block->index();
      const int jacobian_block_size =
          num_residuals * parameter_block->TangentSize();
      if (parameter_block_index < num_eliminate_blocks) {
        jacobian_pos[k] = e_block_pos;
        e_block_pos += jacobian_block_size;
      } else {
        jacobian_pos[k] = static_cast<int>(f_block_pos);
        f_block_pos += jacobian_block_size;
        if (f_block_pos > std::numeric_limits<int>::max()) {
          LOG(ERROR)
              << "Overlow error. Too many entries in the Jacobian matrix.";
          return false;
        }
      }
    }
    jacobian_pos += active_parameter_blocks.size();
  }
  return true;
}

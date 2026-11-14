// u1439 – ceres::internal::BlockEvaluatePreparer::Prepare
// Trích từ internal/ceres/block_evaluate_preparer.cc, dòng 50–78 (chỉ để xem, không compile)

void BlockEvaluatePreparer::Prepare(const ResidualBlock* residual_block,
                                    int residual_block_index,
                                    SparseMatrix* jacobian,
                                    double** jacobians) {
  // If the overall jacobian is not available, use the scratch space.
  if (jacobian == nullptr) {
    scratch_evaluate_preparer_.Prepare(
        residual_block, residual_block_index, jacobian, jacobians);
    return;
  }

  double* jacobian_values =
      down_cast<BlockSparseMatrix*>(jacobian)->mutable_values();

  const int* jacobian_block_offset = jacobian_layout_[residual_block_index];
  const int num_parameter_blocks = residual_block->NumParameterBlocks();
  for (int j = 0; j < num_parameter_blocks; ++j) {
    if (!residual_block->parameter_blocks()[j]->IsConstant()) {
      jacobians[j] = jacobian_values + *jacobian_block_offset;

      // The jacobian_block_offset can't be indexed with 'j' since the code
      // that creates the layout strips out any blocks for inactive
      // parameters. Instead, bump the pointer for active parameters only.
      jacobian_block_offset++;
    } else {
      jacobians[j] = nullptr;
    }
  }
}

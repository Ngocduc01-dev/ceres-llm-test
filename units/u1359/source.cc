// u1359 – ceres::internal::ScratchEvaluatePreparer::Prepare
// Trích từ internal/ceres/scratch_evaluate_preparer.cc, dòng 58–75 (chỉ để xem, không compile)

void ScratchEvaluatePreparer::Prepare(const ResidualBlock* residual_block,
                                      int /* residual_block_index */,
                                      SparseMatrix* /* jacobian */,
                                      double** jacobians) {
  double* jacobian_block_cursor = jacobian_scratch_.get();
  int num_residuals = residual_block->NumResiduals();
  int num_parameter_blocks = residual_block->NumParameterBlocks();
  for (int j = 0; j < num_parameter_blocks; ++j) {
    const ParameterBlock* parameter_block =
        residual_block->parameter_blocks()[j];
    if (parameter_block->IsConstant()) {
      jacobians[j] = nullptr;
    } else {
      jacobians[j] = jacobian_block_cursor;
      jacobian_block_cursor += num_residuals * parameter_block->TangentSize();
    }
  }
}

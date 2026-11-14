// u1289 – ceres::internal::InvalidateEvaluation
// Trích từ internal/ceres/residual_block_utils.cc, dòng 48–63 (chỉ để xem, không compile)

void InvalidateEvaluation(const ResidualBlock& block,
                          double* cost,
                          double* residuals,
                          double** jacobians) {
  const int num_parameter_blocks = block.NumParameterBlocks();
  const int num_residuals = block.NumResiduals();

  InvalidateArray(1, cost);
  InvalidateArray(num_residuals, residuals);
  if (jacobians != nullptr) {
    for (int i = 0; i < num_parameter_blocks; ++i) {
      const int parameter_block_size = block.parameter_blocks()[i]->Size();
      InvalidateArray(num_residuals * parameter_block_size, jacobians[i]);
    }
  }
}

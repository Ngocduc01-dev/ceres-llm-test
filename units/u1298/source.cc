// u1298 – ceres::internal::IsEvaluationValid
// Trích từ internal/ceres/residual_block_utils.cc, dòng 121–142 (chỉ để xem, không compile)

bool IsEvaluationValid(const ResidualBlock& block,
                       double const* const* /*parameters*/,
                       double* residuals,
                       double** jacobians) {
  const int num_parameter_blocks = block.NumParameterBlocks();
  const int num_residuals = block.NumResiduals();

  if (!IsArrayValid(num_residuals, residuals)) {
    return false;
  }

  if (jacobians != nullptr) {
    for (int i = 0; i < num_parameter_blocks; ++i) {
      const int parameter_block_size = block.parameter_blocks()[i]->Size();
      if (!IsArrayValid(num_residuals * parameter_block_size, jacobians[i])) {
        return false;
      }
    }
  }

  return true;
}

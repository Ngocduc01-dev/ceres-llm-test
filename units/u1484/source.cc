// u1484 – ceres::Problem::EvaluateResidualBlockAssumingParametersUnchanged
// Trích từ internal/ceres/problem.cc, dòng 149–161 (chỉ để xem, không compile)

bool Problem::EvaluateResidualBlockAssumingParametersUnchanged(
    ResidualBlockId residual_block_id,
    bool apply_loss_function,
    double* cost,
    double* residuals,
    double** jacobians) const {
  return impl_->EvaluateResidualBlock(residual_block_id,
                                      apply_loss_function,
                                      /* new_point = */ false,
                                      cost,
                                      residuals,
                                      jacobians);
}

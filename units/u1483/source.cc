// u1483 – ceres::Problem::EvaluateResidualBlock
// Trích từ internal/ceres/problem.cc, dòng 136–147 (chỉ để xem, không compile)

bool Problem::EvaluateResidualBlock(ResidualBlockId residual_block_id,
                                    bool apply_loss_function,
                                    double* cost,
                                    double* residuals,
                                    double** jacobians) const {
  return impl_->EvaluateResidualBlock(residual_block_id,
                                      apply_loss_function,
                                      /* new_point = */ true,
                                      cost,
                                      residuals,
                                      jacobians);
}

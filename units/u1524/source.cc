// u1524 – ceres::Problem::AddResidualBlock
// Trích từ internal/ceres/problem.cc, dòng 60–66 (chỉ để xem, không compile)

ResidualBlockId Problem::AddResidualBlock(CostFunction* cost_function,
                                          LossFunction* loss_function,
                                          double* const* const parameter_blocks,
                                          int num_parameter_blocks) {
  return impl_->AddResidualBlock(
      cost_function, loss_function, parameter_blocks, num_parameter_blocks);
}

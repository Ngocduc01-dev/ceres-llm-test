// u1523 – ceres::Problem::AddResidualBlock
// Trích từ internal/ceres/problem.cc, dòng 50–58 (chỉ để xem, không compile)

ResidualBlockId Problem::AddResidualBlock(
    CostFunction* cost_function,
    LossFunction* loss_function,
    const std::vector<double*>& parameter_blocks) {
  return impl_->AddResidualBlock(cost_function,
                                 loss_function,
                                 parameter_blocks.data(),
                                 static_cast<int>(parameter_blocks.size()));
}

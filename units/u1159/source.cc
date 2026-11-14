// u1159 – ceres::internal::ProblemImpl::GetLossFunctionForResidualBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 860–863 (chỉ để xem, không compile)

const LossFunction* ProblemImpl::GetLossFunctionForResidualBlock(
    const ResidualBlockId residual_block) const {
  return residual_block->loss_function();
}

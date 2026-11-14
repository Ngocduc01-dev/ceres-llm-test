// u1158 – ceres::internal::ProblemImpl::GetCostFunctionForResidualBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 855–858 (chỉ để xem, không compile)

const CostFunction* ProblemImpl::GetCostFunctionForResidualBlock(
    const ResidualBlockId residual_block) const {
  return residual_block->cost_function();
}

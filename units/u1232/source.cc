// u1232 – ceres::internal::ProblemImpl::DeleteBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 201–219 (chỉ để xem, không compile)

void ProblemImpl::DeleteBlock(ResidualBlock* residual_block) {
  // The const casts here are legit, since ResidualBlock holds these
  // pointers as const pointers but we have ownership of them and
  // have the right to destroy them when the destructor is called.
  auto* cost_function =
      const_cast<CostFunction*>(residual_block->cost_function());
  if (options_.cost_function_ownership == TAKE_OWNERSHIP) {
    DecrementValueOrDeleteKey(cost_function, &cost_function_ref_count_);
  }

  auto* loss_function =
      const_cast<LossFunction*>(residual_block->loss_function());
  if (options_.loss_function_ownership == TAKE_OWNERSHIP &&
      loss_function != nullptr) {
    DecrementValueOrDeleteKey(loss_function, &loss_function_ref_count_);
  }

  delete residual_block;
}

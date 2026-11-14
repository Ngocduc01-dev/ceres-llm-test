// u1205 – ceres::ConditionedCostFunction::ConditionedCostFunction
// Trích từ internal/ceres/conditioned_cost_function.cc, dòng 46–67 (chỉ để xem, không compile)

ConditionedCostFunction::ConditionedCostFunction(
    CostFunction* wrapped_cost_function,
    const std::vector<CostFunction*>& conditioners,
    Ownership ownership)
    : wrapped_cost_function_(wrapped_cost_function),
      conditioners_(conditioners),
      ownership_(ownership) {
  // Set up our dimensions.
  set_num_residuals(wrapped_cost_function_->num_residuals());
  *mutable_parameter_block_sizes() =
      wrapped_cost_function_->parameter_block_sizes();

  // Sanity-check the conditioners' dimensions.
  CHECK_EQ(wrapped_cost_function_->num_residuals(), conditioners_.size());
  for (int i = 0; i < wrapped_cost_function_->num_residuals(); i++) {
    if (conditioners[i]) {
      CHECK_EQ(1, conditioners[i]->num_residuals());
      CHECK_EQ(1, conditioners[i]->parameter_block_sizes().size());
      CHECK_EQ(1, conditioners[i]->parameter_block_sizes()[0]);
    }
  }
}

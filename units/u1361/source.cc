// u1361 – ceres::GradientChecker::GradientChecker
// Trích từ internal/ceres/gradient_checker.cc, dòng 116–139 (chỉ để xem, không compile)

GradientChecker::GradientChecker(const CostFunction* function,
                                 const std::vector<const Manifold*>* manifolds,
                                 const NumericDiffOptions& options)
    : function_(function) {
  CHECK(function != nullptr);
  if (manifolds != nullptr) {
    manifolds_ = *manifolds;
  } else {
    manifolds_.resize(function->parameter_block_sizes().size(), nullptr);
  }

  auto finite_diff_cost_function =
      std::make_unique<DynamicNumericDiffCostFunction<CostFunction, RIDDERS>>(
          function, DO_NOT_TAKE_OWNERSHIP, options);
  const std::vector<int32_t>& parameter_block_sizes =
      function->parameter_block_sizes();
  const int num_parameter_blocks = parameter_block_sizes.size();
  for (int i = 0; i < num_parameter_blocks; ++i) {
    finite_diff_cost_function->AddParameterBlock(parameter_block_sizes[i]);
  }
  finite_diff_cost_function->SetNumResiduals(function->num_residuals());

  finite_diff_cost_function_ = std::move(finite_diff_cost_function);
}

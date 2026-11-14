// u1449 – ceres::internal::(anonymous)::GradientCheckingCostFunction::GradientCheckingCostFunction
// Trích từ internal/ceres/gradient_checking_cost_function.cc, dòng 61–77 (chỉ để xem, không compile)

  GradientCheckingCostFunction(const CostFunction* function,
                               const std::vector<const Manifold*>* manifolds,
                               const NumericDiffOptions& options,
                               double relative_precision,
                               std::string extra_info,
                               GradientCheckingIterationCallback* callback)
      : function_(function),
        gradient_checker_(function, manifolds, options),
        relative_precision_(relative_precision),
        extra_info_(std::move(extra_info)),
        callback_(callback) {
    CHECK(callback_ != nullptr);
    const std::vector<int32_t>& parameter_block_sizes =
        function->parameter_block_sizes();
    *mutable_parameter_block_sizes() = parameter_block_sizes;
    set_num_residuals(function->num_residuals());
  }

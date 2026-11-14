// u0859 – ceres::internal::CreateGradientCheckingCostFunction
// Trích từ internal/ceres/gradient_checking_cost_function.cc, dòng 150–166 (chỉ để xem, không compile)

std::unique_ptr<CostFunction> CreateGradientCheckingCostFunction(
    const CostFunction* cost_function,
    const std::vector<const Manifold*>* manifolds,
    double relative_step_size,
    double relative_precision,
    const std::string& extra_info,
    GradientCheckingIterationCallback* callback) {
  NumericDiffOptions numeric_diff_options;
  numeric_diff_options.relative_step_size = relative_step_size;

  return std::make_unique<GradientCheckingCostFunction>(cost_function,
                                                        manifolds,
                                                        numeric_diff_options,
                                                        relative_precision,
                                                        extra_info,
                                                        callback);
}

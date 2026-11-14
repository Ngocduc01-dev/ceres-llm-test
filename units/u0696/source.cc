// u0696 – ceres::NumericDiffCostFunction::NumericDiffCostFunction<CostFunctor, kMethod, kNumResiduals, Ns...>
// Trích từ include/ceres/numeric_diff_cost_function.h, dòng 185–194 (chỉ để xem, không compile)

  explicit NumericDiffCostFunction(
      CostFunctor* functor,
      Ownership ownership = TAKE_OWNERSHIP,
      int num_residuals = kNumResiduals,
      const NumericDiffOptions& options = NumericDiffOptions())
      : functor_(functor), ownership_(ownership), options_(options) {
    if (kNumResiduals == DYNAMIC) {
      SizedCostFunction<kNumResiduals, Ns...>::set_num_residuals(num_residuals);
    }
  }

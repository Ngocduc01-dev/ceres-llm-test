// u0622 – ceres::DynamicNumericDiffCostFunction::DynamicNumericDiffCostFunction<CostFunctor, kMethod>
// Trích từ include/ceres/dynamic_numeric_diff_cost_function.h, dòng 82–86 (chỉ để xem, không compile)

  explicit DynamicNumericDiffCostFunction(
      const CostFunctor* functor,
      Ownership ownership = TAKE_OWNERSHIP,
      const NumericDiffOptions& options = NumericDiffOptions())
      : functor_(functor), ownership_(ownership), options_(options) {}

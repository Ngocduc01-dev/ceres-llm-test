// u0640 – ceres::NumericDiffCostFunction::NumericDiffCostFunction<CostFunctor, kMethod, kNumResiduals, Ns...>
// Trích từ include/ceres/numeric_diff_cost_function.h, dòng 196–197 (chỉ để xem, không compile)

  NumericDiffCostFunction(NumericDiffCostFunction&& other)
      : functor_(std::move(other.functor_)), ownership_(other.ownership_) {}

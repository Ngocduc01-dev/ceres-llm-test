// u0623 – ceres::DynamicNumericDiffCostFunction::DynamicNumericDiffCostFunction<CostFunctor, kMethod>
// Trích từ include/ceres/dynamic_numeric_diff_cost_function.h, dòng 88–89 (chỉ để xem, không compile)

  DynamicNumericDiffCostFunction(DynamicNumericDiffCostFunction&& other)
      : functor_(std::move(other.functor_)), ownership_(other.ownership_) {}

// u0621 – ceres::DynamicAutoDiffCostFunction::DynamicAutoDiffCostFunction<CostFunctor, Stride>
// Trích từ include/ceres/dynamic_autodiff_cost_function.h, dòng 87–88 (chỉ để xem, không compile)

  DynamicAutoDiffCostFunction(DynamicAutoDiffCostFunction&& other)
      : functor_(std::move(other.functor_)), ownership_(other.ownership_) {}

// u0615 – ceres::AutoDiffCostFunction::AutoDiffCostFunction<CostFunctor, kNumResiduals, Ns...>
// Trích từ include/ceres/autodiff_cost_function.h, dòng 182–183 (chỉ để xem, không compile)

  AutoDiffCostFunction(AutoDiffCostFunction&& other)
      : functor_(std::move(other.functor_)), ownership_(other.ownership_) {}

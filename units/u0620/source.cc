// u0620 – ceres::DynamicAutoDiffCostFunction::DynamicAutoDiffCostFunction<CostFunctor, Stride>
// Trích từ include/ceres/dynamic_autodiff_cost_function.h, dòng 83–85 (chỉ để xem, không compile)

  explicit DynamicAutoDiffCostFunction(CostFunctor* functor,
                                       Ownership ownership = TAKE_OWNERSHIP)
      : functor_(functor), ownership_(ownership) {}

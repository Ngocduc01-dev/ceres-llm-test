// u0647 – ceres::TinySolverAutoDiffFunction::TinySolverAutoDiffFunction<CostFunctor, kNumResiduals, kNumParameters, T>
// Trích từ include/ceres/tiny_solver_autodiff_function.h, dòng 116–119 (chỉ để xem, không compile)

  explicit TinySolverAutoDiffFunction(const CostFunctor& cost_functor)
      : cost_functor_(cost_functor) {
    Initialize<kNumResiduals>(cost_functor);
  }

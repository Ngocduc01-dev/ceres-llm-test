// u0614 – ceres::AutoDiffCostFunction::AutoDiffCostFunction<CostFunctor, kNumResiduals, Ns...>
// Trích từ include/ceres/autodiff_cost_function.h, dòng 172–180 (chỉ để xem, không compile)

  AutoDiffCostFunction(CostFunctor* functor,
                       int num_residuals,
                       Ownership ownership = TAKE_OWNERSHIP)
      : functor_(functor), ownership_(ownership) {
    static_assert(kNumResiduals == DYNAMIC,
                  "Can't run the dynamic-size constructor if the number of "
                  "residuals is not ceres::DYNAMIC.");
    SizedCostFunction<kNumResiduals, Ns...>::set_num_residuals(num_residuals);
  }

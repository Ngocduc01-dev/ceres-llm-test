// u0613 – ceres::AutoDiffCostFunction::AutoDiffCostFunction<CostFunctor, kNumResiduals, Ns...>
// Trích từ include/ceres/autodiff_cost_function.h, dòng 159–165 (chỉ để xem, không compile)

  explicit AutoDiffCostFunction(CostFunctor* functor,
                                Ownership ownership = TAKE_OWNERSHIP)
      : functor_(functor), ownership_(ownership) {
    static_assert(kNumResiduals != DYNAMIC,
                  "Can't run the fixed-size constructor if the number of "
                  "residuals is set to ceres::DYNAMIC.");
  }

// u0455 – ceres::NumericDiffCostFunction::~NumericDiffCostFunction<CostFunctor, kMethod, kNumResiduals, Ns...>
// Trích từ include/ceres/numeric_diff_cost_function.h, dòng 199–203 (chỉ để xem, không compile)

  virtual ~NumericDiffCostFunction() {
    if (ownership_ != TAKE_OWNERSHIP) {
      functor_.release();
    }
  }

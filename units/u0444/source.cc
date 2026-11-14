// u0444 – ceres::DynamicNumericDiffCostFunction::~DynamicNumericDiffCostFunction<CostFunctor, kMethod>
// Trích từ include/ceres/dynamic_numeric_diff_cost_function.h, dòng 91–95 (chỉ để xem, không compile)

  ~DynamicNumericDiffCostFunction() override {
    if (ownership_ != TAKE_OWNERSHIP) {
      functor_.release();
    }
  }

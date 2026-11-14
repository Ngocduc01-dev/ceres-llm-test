// u0904 – ceres::DynamicCostFunctionToFunctor::DynamicCostFunctionToFunctor
// Trích từ include/ceres/dynamic_cost_function_to_functor.h, dòng 108–111 (chỉ để xem, không compile)

  explicit DynamicCostFunctionToFunctor(CostFunction* cost_function)
      : cost_function_(cost_function) {
    CHECK(cost_function != nullptr);
  }

// u0020 – ceres::DynamicCostFunctionToFunctor::operator()
// Trích từ include/ceres/dynamic_cost_function_to_functor.h, dòng 113–115 (chỉ để xem, không compile)

  bool operator()(double const* const* parameters, double* residuals) const {
    return cost_function_->Evaluate(parameters, residuals, nullptr);
  }

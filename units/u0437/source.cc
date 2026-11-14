// u0437 – ceres::AutoDiffCostFunction::Evaluate
// Trích từ include/ceres/autodiff_cost_function.h, dòng 201–217 (chỉ để xem, không compile)

  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    using ParameterDims =
        typename SizedCostFunction<kNumResiduals, Ns...>::ParameterDims;

    if (!jacobians) {
      return internal::VariadicEvaluate<ParameterDims>(
          *functor_, parameters, residuals);
    }
    return internal::AutoDifferentiate<kNumResiduals, ParameterDims>(
        *functor_,
        parameters,
        SizedCostFunction<kNumResiduals, Ns...>::num_residuals(),
        residuals,
        jacobians);
  };

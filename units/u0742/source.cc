// u0742 – ceres::NumericDiffCostFunction::Evaluate
// Trích từ include/ceres/numeric_diff_cost_function.h, dòng 205–248 (chỉ để xem, không compile)

  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    using internal::FixedArray;
    using internal::NumericDiff;

    using ParameterDims =
        typename SizedCostFunction<kNumResiduals, Ns...>::ParameterDims;

    constexpr int kNumParameters = ParameterDims::kNumParameters;
    constexpr int kNumParameterBlocks = ParameterDims::kNumParameterBlocks;

    // Get the function value (residuals) at the the point to evaluate.
    if (!internal::VariadicEvaluate<ParameterDims>(
            *functor_, parameters, residuals)) {
      return false;
    }

    if (jacobians == nullptr) {
      return true;
    }

    // Create a copy of the parameters which will get mutated.
    FixedArray<double> parameters_copy(kNumParameters);
    std::array<double*, kNumParameterBlocks> parameters_reference_copy =
        ParameterDims::GetUnpackedParameters(parameters_copy.data());

    for (int block = 0; block < kNumParameterBlocks; ++block) {
      memcpy(parameters_reference_copy[block],
             parameters[block],
             sizeof(double) * ParameterDims::GetDim(block));
    }

    internal::EvaluateJacobianForParameterBlocks<ParameterDims>::
        template Apply<kMethod, kNumResiduals>(
            functor_.get(),
            residuals,
            options_,
            SizedCostFunction<kNumResiduals, Ns...>::num_residuals(),
            parameters_reference_copy.data(),
            jacobians);

    return true;
  }

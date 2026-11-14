// u0743 – ceres::NumericDiffFirstOrderFunction::Evaluate
// Trích từ include/ceres/numeric_diff_first_order_function.h, dòng 158–201 (chỉ để xem, không compile)

  bool Evaluate(const double* const parameters,
                double* cost,
                double* gradient) const override {
    // Get the function value (cost) at the the point to evaluate.
    if (!(*functor_)(parameters, cost)) {
      return false;
    }

    if (gradient == nullptr) {
      return true;
    }

    // Create a copy of the parameters which will get mutated.
    internal::FixedArray<double, 32> parameters_copy(num_parameters_);
    std::copy_n(parameters, num_parameters_, parameters_copy.data());
    double* parameters_ptr = parameters_copy.data();
    constexpr int kNumResiduals = 1;
    if constexpr (kNumParameters == DYNAMIC) {
      internal::FirstOrderFunctorAdapter<FirstOrderFunctor> fofa(*functor_);
      return internal::NumericDiff<
          internal::FirstOrderFunctorAdapter<FirstOrderFunctor>,
          kMethod,
          kNumResiduals,
          internal::DynamicParameterDims,
          0,
          DYNAMIC>::EvaluateJacobianForParameterBlock(&fofa,
                                                      cost,
                                                      options_,
                                                      kNumResiduals,
                                                      0,
                                                      num_parameters_,
                                                      &parameters_ptr,
                                                      gradient);
    } else {
      return internal::EvaluateJacobianForParameterBlocks<
          internal::StaticParameterDims<kNumParameters>>::
          template Apply<kMethod, 1>(functor_.get(),
                                     cost,
                                     options_,
                                     kNumResiduals,
                                     &parameters_ptr,
                                     &gradient);
    }
  }

// u0772 – ceres::internal::AutoDifferentiate
// Trích từ include/ceres/internal/autodiff.h, dòng 303–359 (chỉ để xem, không compile)

template <int kNumResiduals,
          typename ParameterDims,
          typename Functor,
          typename T>
inline bool AutoDifferentiate(const Functor& functor,
                              T const* const* parameters,
                              int dynamic_num_outputs,
                              T* function_value,
                              T** jacobians) {
  using JetT = Jet<T, ParameterDims::kNumParameters>;
  using Parameters = typename ParameterDims::Parameters;

  if (kNumResiduals != DYNAMIC) {
    DCHECK_EQ(kNumResiduals, dynamic_num_outputs);
  }

  ArraySelector<JetT,
                ParameterDims::kNumParameters,
                CERES_AUTODIFF_MAX_PARAMETERS_ON_STACK>
      parameters_as_jets(ParameterDims::kNumParameters);

  // Pointers to the beginning of each parameter block
  std::array<JetT*, ParameterDims::kNumParameterBlocks> unpacked_parameters =
      ParameterDims::GetUnpackedParameters(parameters_as_jets.data());

  // If the number of residuals is fixed, we use the template argument as the
  // number of outputs. Otherwise we use the num_outputs parameter. Note: The
  // ?-operator here is compile-time evaluated, therefore num_outputs is also
  // a compile-time constant for functors with fixed residuals.
  const int num_outputs =
      kNumResiduals == DYNAMIC ? dynamic_num_outputs : kNumResiduals;
  DCHECK_GT(num_outputs, 0);

  ArraySelector<JetT, kNumResiduals, CERES_AUTODIFF_MAX_RESIDUALS_ON_STACK>
      residuals_as_jets(num_outputs);

  // Invalidate the output Jets, so that we can detect if the user
  // did not assign values to all of them.
  for (int i = 0; i < num_outputs; ++i) {
    residuals_as_jets[i].a = kImpossibleValue;
    residuals_as_jets[i].v.setConstant(kImpossibleValue);
  }

  Make1stOrderPerturbations<Parameters>::Apply(parameters,
                                               parameters_as_jets.data());

  if (!VariadicEvaluate<ParameterDims>(
          functor, unpacked_parameters.data(), residuals_as_jets.data())) {
    return false;
  }

  Take0thOrderPart(num_outputs, residuals_as_jets.data(), function_value);
  Take1stOrderParts<Parameters>::Apply(
      num_outputs, residuals_as_jets.data(), jacobians);

  return true;
}

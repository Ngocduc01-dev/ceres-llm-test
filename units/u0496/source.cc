// u0496 – ceres::internal::EvaluateJacobianForParameterBlocks::Apply
// Trích từ include/ceres/internal/numeric_diff.h, dòng 446–483 (chỉ để xem, không compile)

  template <NumericDiffMethodType method,
            int kNumResiduals,
            typename CostFunctor>
  static bool Apply(const CostFunctor* functor,
                    const double* residuals_at_eval_point,
                    const NumericDiffOptions& options,
                    int num_residuals,
                    double** parameters,
                    double** jacobians) {
    if (jacobians[ParameterIdx] != nullptr) {
      if (!NumericDiff<
              CostFunctor,
              method,
              kNumResiduals,
              ParameterDims,
              ParameterIdx,
              N>::EvaluateJacobianForParameterBlock(functor,
                                                    residuals_at_eval_point,
                                                    options,
                                                    num_residuals,
                                                    ParameterIdx,
                                                    N,
                                                    parameters,
                                                    jacobians[ParameterIdx])) {
        return false;
      }
    }

    return EvaluateJacobianForParameterBlocks<ParameterDims,
                                              std::integer_sequence<int, Ns...>,
                                              ParameterIdx + 1>::
        template Apply<method, kNumResiduals>(functor,
                                              residuals_at_eval_point,
                                              options,
                                              num_residuals,
                                              parameters,
                                              jacobians);
  }

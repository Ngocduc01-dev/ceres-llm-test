// u0059 – ceres::internal::EvaluateJacobianForParameterBlocks::Apply
// Trích từ include/ceres/internal/numeric_diff.h, dòng 491–501 (chỉ để xem, không compile)

  template <NumericDiffMethodType method,
            int kNumResiduals,
            typename CostFunctor>
  static bool Apply(const CostFunctor* /* NOT USED*/,
                    const double* /* NOT USED*/,
                    const NumericDiffOptions& /* NOT USED*/,
                    int /* NOT USED*/,
                    double** /* NOT USED*/,
                    double** /* NOT USED*/) {
    return true;
  }

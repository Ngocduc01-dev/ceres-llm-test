// u1001 – ceres::internal::GradientProblemEvaluator::NumEffectiveParameters
// Trích từ internal/ceres/gradient_problem_evaluator.h, dòng 84–86 (chỉ để xem, không compile)

  int NumEffectiveParameters() const final {
    return problem_.NumTangentParameters();
  }

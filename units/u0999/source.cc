// u0999 – ceres::internal::GradientProblemEvaluator::Plus
// Trích từ internal/ceres/gradient_problem_evaluator.h, dòng 76–80 (chỉ để xem, không compile)

  bool Plus(const double* state,
            const double* delta,
            double* state_plus_delta) const final {
    return problem_.Plus(state, delta, state_plus_delta);
  }

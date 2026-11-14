// u1250 – ceres::internal::ProgramEvaluator::Plus
// Trích từ internal/ceres/program_evaluator.h, dòng 303–308 (chỉ để xem, không compile)

  bool Plus(const double* state,
            const double* delta,
            double* state_plus_delta) const final {
    return program_->Plus(
        state, delta, state_plus_delta, options_.context, options_.num_threads);
  }

// u0869 – ceres::internal::LineSearchFunction::LineSearchFunction
// Trích từ internal/ceres/line_search.cc, dòng 88–94 (chỉ để xem, không compile)

LineSearchFunction::LineSearchFunction(Evaluator* evaluator)
    : evaluator_(evaluator),
      position_(evaluator->NumParameters()),
      direction_(evaluator->NumEffectiveParameters()),
      scaled_direction_(evaluator->NumEffectiveParameters()),
      initial_evaluator_residual_time_in_seconds(0.0),
      initial_evaluator_jacobian_time_in_seconds(0.0) {}

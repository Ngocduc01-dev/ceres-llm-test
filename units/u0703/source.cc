// u0703 – ceres::internal::GradientProblemSolverStateUpdatingCallback::operator()
// Trích từ internal/ceres/callbacks.cc, dòng 68–74 (chỉ để xem, không compile)

CallbackReturnType GradientProblemSolverStateUpdatingCallback::operator()(
    const IterationSummary& summary) {
  if (summary.step_is_successful) {
    std::copy_n(internal_parameters_, num_parameters_, user_parameters_);
  }
  return SOLVER_CONTINUE;
}

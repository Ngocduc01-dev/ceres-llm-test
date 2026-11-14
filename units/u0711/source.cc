// u0711 – ceres::internal::GradientCheckingIterationCallback::operator()
// Trích từ internal/ceres/gradient_checking_cost_function.cc, dòng 134–141 (chỉ để xem, không compile)

CallbackReturnType GradientCheckingIterationCallback::operator()(
    const IterationSummary& /*summary*/) {
  if (gradient_error_detected_) {
    LOG(ERROR) << "Gradient error detected. Terminating solver.";
    return SOLVER_ABORT;
  }
  return SOLVER_CONTINUE;
}

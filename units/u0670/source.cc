// u0670 – ceres::internal::GradientCheckingIterationCallback::SetGradientErrorDetected
// Trích từ internal/ceres/gradient_checking_cost_function.cc, dòng 143–148 (chỉ để xem, không compile)

void GradientCheckingIterationCallback::SetGradientErrorDetected(
    std::string& error_log) {
  std::lock_guard<std::mutex> l(mutex_);
  gradient_error_detected_ = true;
  error_log_ += "\n" + error_log;
}

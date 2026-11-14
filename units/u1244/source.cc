// u1244 – ceres::internal::FunctionSample::ToDebugString
// Trích từ internal/ceres/function_sample.cc, dòng 66–75 (chỉ để xem, không compile)

std::string FunctionSample::ToDebugString() const {
  return StringPrintf(
      "[x: %.8e, value: %.8e, gradient: %.8e, "
      "value_is_valid: %d, gradient_is_valid: %d]",
      x,
      value,
      gradient,
      value_is_valid,
      gradient_is_valid);
}

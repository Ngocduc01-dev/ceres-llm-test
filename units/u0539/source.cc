// u0539 – ceres::internal::IsClose
// Trích từ internal/ceres/is_close.cc, dòng 37–58 (chỉ để xem, không compile)

bool IsClose(double x,
             double y,
             double relative_precision,
             double* relative_error,
             double* absolute_error) {
  double local_absolute_error;
  double local_relative_error;
  if (!absolute_error) {
    absolute_error = &local_absolute_error;
  }
  if (!relative_error) {
    relative_error = &local_relative_error;
  }
  *absolute_error = std::fabs(x - y);
  *relative_error = *absolute_error / std::max(std::fabs(x), std::fabs(y));
  if (x == 0 || y == 0) {
    // If x or y is exactly zero, then relative difference doesn't have any
    // meaning. Take the absolute difference instead.
    *relative_error = *absolute_error;
  }
  return *relative_error < std::fabs(relative_precision);
}

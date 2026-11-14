// u0537 – ceres::internal::FindInvalidValue
// Trích từ internal/ceres/array_utils.cc, dòng 55–67 (chỉ để xem, không compile)

int64_t FindInvalidValue(const int64_t size, const double* x) {
  if (x == nullptr) {
    return size;
  }

  for (int64_t i = 0; i < size; ++i) {
    if (!std::isfinite(x[i]) || (x[i] == kImpossibleValue)) {
      return i;
    }
  }

  return size;
}

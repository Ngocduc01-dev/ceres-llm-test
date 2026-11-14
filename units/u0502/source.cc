// u0502 – ceres::internal::InvalidateArray
// Trích từ internal/ceres/array_utils.cc, dòng 69–75 (chỉ để xem, không compile)

void InvalidateArray(const int64_t size, double* x) {
  if (x != nullptr) {
    for (int64_t i = 0; i < size; ++i) {
      x[i] = kImpossibleValue;
    }
  }
}

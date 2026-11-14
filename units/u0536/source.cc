// u0536 – ceres::internal::IsArrayValid
// Trích từ internal/ceres/array_utils.cc, dòng 44–53 (chỉ để xem, không compile)

bool IsArrayValid(const int64_t size, const double* x) {
  if (x != nullptr) {
    for (int64_t i = 0; i < size; ++i) {
      if (!std::isfinite(x[i]) || (x[i] == kImpossibleValue)) {
        return false;
      }
    }
  }
  return true;
}

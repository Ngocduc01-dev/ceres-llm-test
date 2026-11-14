// u0147 – ceres::IsInfinite
// Trích từ include/ceres/jet.h, dòng 1073–1079 (chỉ để xem, không compile)

template <typename T, int N>
CERES_DEPRECATED_WITH_MSG(
    "ceres::IsInfinite will be removed in a future Ceres Solver release. "
    "Please use ceres::isinf.")
inline bool IsInfinite(const Jet<T, N>& f) {
  return isinf(f);
}

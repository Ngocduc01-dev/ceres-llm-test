// u0144 – ceres::IsFinite
// Trích từ include/ceres/jet.h, dòng 1048–1054 (chỉ để xem, không compile)

template <typename T, int N>
CERES_DEPRECATED_WITH_MSG(
    "ceres::IsFinite will be removed in a future Ceres Solver release. Please "
    "use ceres::isfinite.")
inline bool IsFinite(const Jet<T, N>& f) {
  return isfinite(f);
}

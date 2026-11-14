// u0145 – ceres::IsNaN
// Trích từ include/ceres/jet.h, dòng 1056–1062 (chỉ để xem, không compile)

template <typename T, int N>
CERES_DEPRECATED_WITH_MSG(
    "ceres::IsNaN will be removed in a future Ceres Solver release. Please use "
    "ceres::isnan.")
inline bool IsNaN(const Jet<T, N>& f) {
  return isnan(f);
}

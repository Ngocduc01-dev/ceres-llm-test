// u0146 – ceres::IsNormal
// Trích từ include/ceres/jet.h, dòng 1064–1070 (chỉ để xem, không compile)

template <typename T, int N>
CERES_DEPRECATED_WITH_MSG(
    "ceres::IsNormal will be removed in a future Ceres Solver release. Please "
    "use ceres::isnormal.")
inline bool IsNormal(const Jet<T, N>& f) {
  return isnormal(f);
}

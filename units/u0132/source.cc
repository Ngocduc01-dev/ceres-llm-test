// u0132 – ceres::isfinite
// Trích từ include/ceres/jet.h, dòng 940–943 (chỉ để xem, không compile)

template <typename T, int N>
inline bool isfinite(const Jet<T, N>& f) {
  return isfinite(f.a);
}

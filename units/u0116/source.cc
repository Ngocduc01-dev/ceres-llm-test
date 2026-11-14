// u0116 – ceres::floor
// Trích từ include/ceres/jet.h, dòng 674–677 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> floor(const Jet<T, N>& f) {
  return Jet<T, N>(floor(f.a));
}

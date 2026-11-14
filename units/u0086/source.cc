// u0086 – ceres::operator*
// Trích từ include/ceres/jet.h, dòng 360–363 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> operator*(T s, const Jet<T, N>& f) {
  return Jet<T, N>(f.a * s, f.v * s);
}

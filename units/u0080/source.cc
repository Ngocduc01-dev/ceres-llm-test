// u0080 – ceres::operator+
// Trích từ include/ceres/jet.h, dòng 324–327 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> operator+(T s, const Jet<T, N>& f) {
  return Jet<T, N>(f.a + s, f.v);
}

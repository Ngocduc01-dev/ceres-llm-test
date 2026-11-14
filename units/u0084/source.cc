// u0084 – ceres::operator*
// Trích từ include/ceres/jet.h, dòng 348–351 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> operator*(const Jet<T, N>& f, const Jet<T, N>& g) {
  return Jet<T, N>(f.a * g.a, f.a * g.v + f.v * g.a);
}

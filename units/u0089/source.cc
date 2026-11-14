// u0089 – ceres::operator/
// Trích từ include/ceres/jet.h, dòng 388–392 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> operator/(const Jet<T, N>& f, T s) {
  const T s_inverse = T(1.0) / s;
  return Jet<T, N>(f.a * s_inverse, f.v * s_inverse);
}

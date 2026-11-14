// u0087 – ceres::operator/
// Trích từ include/ceres/jet.h, dòng 366–378 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> operator/(const Jet<T, N>& f, const Jet<T, N>& g) {
  // This uses:
  //
  //   a + u   (a + u)(b - v)   (a + u)(b - v)
  //   ----- = -------------- = --------------
  //   b + v   (b + v)(b - v)        b^2
  //
  // which holds because v*v = 0.
  const T g_a_inverse = T(1.0) / g.a;
  const T f_a_by_g_a = f.a * g_a_inverse;
  return Jet<T, N>(f_a_by_g_a, (f.v - f_a_by_g_a * g.v) * g_a_inverse);
}

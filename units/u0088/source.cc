// u0088 – ceres::operator/
// Trích từ include/ceres/jet.h, dòng 381–385 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> operator/(T s, const Jet<T, N>& g) {
  const T minus_s_g_a_inverse2 = -s / (g.a * g.a);
  return Jet<T, N>(s / g.a, g.v * minus_s_g_a_inverse2);
}

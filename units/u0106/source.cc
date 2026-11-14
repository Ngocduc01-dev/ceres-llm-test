// u0106 – ceres::sqrt
// Trích từ include/ceres/jet.h, dòng 602–607 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> sqrt(const Jet<T, N>& f) {
  const T tmp = sqrt(f.a);
  const T two_a_inverse = T(1.0) / (T(2.0) * tmp);
  return Jet<T, N>(tmp, f.v * two_a_inverse);
}

// u0105 – ceres::expm1
// Trích từ include/ceres/jet.h, dòng 594–599 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> expm1(const Jet<T, N>& f) {
  const T tmp = expm1(f.a);
  const T expa = tmp + T(1.0);  // exp(a) = expm1(a) + 1
  return Jet<T, N>(tmp, expa * f.v);
}

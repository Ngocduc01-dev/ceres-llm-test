// u0118 – ceres::cbrt
// Trích từ include/ceres/jet.h, dòng 691–695 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> cbrt(const Jet<T, N>& f) {
  const T derivative = T(1.0) / (T(3.0) * cbrt(f.a * f.a));
  return Jet<T, N>(cbrt(f.a), f.v * derivative);
}

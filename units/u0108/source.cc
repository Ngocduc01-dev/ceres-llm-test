// u0108 – ceres::acos
// Trích từ include/ceres/jet.h, dòng 616–620 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> acos(const Jet<T, N>& f) {
  const T tmp = -T(1.0) / sqrt(T(1.0) - f.a * f.a);
  return Jet<T, N>(acos(f.a), tmp * f.v);
}

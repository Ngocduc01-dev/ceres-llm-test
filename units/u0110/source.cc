// u0110 – ceres::asin
// Trích từ include/ceres/jet.h, dòng 629–633 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> asin(const Jet<T, N>& f) {
  const T tmp = T(1.0) / sqrt(T(1.0) - f.a * f.a);
  return Jet<T, N>(asin(f.a), tmp * f.v);
}

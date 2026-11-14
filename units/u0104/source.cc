// u0104 – ceres::exp
// Trích từ include/ceres/jet.h, dòng 587–591 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> exp(const Jet<T, N>& f) {
  const T tmp = exp(f.a);
  return Jet<T, N>(tmp, tmp * f.v);
}

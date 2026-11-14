// u0115 – ceres::tanh
// Trích từ include/ceres/jet.h, dòng 663–668 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> tanh(const Jet<T, N>& f) {
  const T tanh_a = tanh(f.a);
  const T tmp = T(1.0) - tanh_a * tanh_a;
  return Jet<T, N>(tanh_a, tmp * f.v);
}

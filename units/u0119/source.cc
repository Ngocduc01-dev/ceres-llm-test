// u0119 – ceres::exp2
// Trích từ include/ceres/jet.h, dòng 698–703 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> exp2(const Jet<T, N>& f) {
  const T tmp = exp2(f.a);
  const T derivative = tmp * log(T(2));
  return Jet<T, N>(tmp, f.v * derivative);
}

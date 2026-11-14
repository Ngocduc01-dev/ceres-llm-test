// u0111 – ceres::tan
// Trích từ include/ceres/jet.h, dòng 636–641 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> tan(const Jet<T, N>& f) {
  const T tan_a = tan(f.a);
  const T tmp = T(1.0) + tan_a * tan_a;
  return Jet<T, N>(tan_a, tmp * f.v);
}

// u0100 – ceres::abs
// Trích từ include/ceres/jet.h, dòng 523–526 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> abs(const Jet<T, N>& f) {
  return Jet<T, N>(abs(f.a), copysign(T(1), f.a) * f.v);
}

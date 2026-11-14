// u0112 – ceres::atan
// Trích từ include/ceres/jet.h, dòng 644–648 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> atan(const Jet<T, N>& f) {
  const T tmp = T(1.0) / (T(1.0) + f.a * f.a);
  return Jet<T, N>(atan(f.a), tmp * f.v);
}

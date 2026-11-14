// u0109 – ceres::sin
// Trích từ include/ceres/jet.h, dòng 623–626 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> sin(const Jet<T, N>& f) {
  return Jet<T, N>(sin(f.a), cos(f.a) * f.v);
}

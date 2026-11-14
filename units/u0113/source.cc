// u0113 – ceres::sinh
// Trích từ include/ceres/jet.h, dòng 651–654 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> sinh(const Jet<T, N>& f) {
  return Jet<T, N>(sinh(f.a), cosh(f.a) * f.v);
}

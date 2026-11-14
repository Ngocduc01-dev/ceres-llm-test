// u0114 – ceres::cosh
// Trích từ include/ceres/jet.h, dòng 657–660 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> cosh(const Jet<T, N>& f) {
  return Jet<T, N>(cosh(f.a), sinh(f.a) * f.v);
}

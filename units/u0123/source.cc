// u0123 – ceres::fma
// Trích từ include/ceres/jet.h, dòng 748–756 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> fma(const Jet<T, N>& x,
                     const Jet<T, N>& y,
                     const Jet<T, N>& z) {
  // d/dx fma(x, y, z) = y
  // d/dy fma(x, y, z) = x
  // d/dz fma(x, y, z) = 1
  return Jet<T, N>(fma(x.a, y.a, z.a), y.a * x.v + x.a * y.v + z.v);
}

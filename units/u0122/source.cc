// u0122 – ceres::hypot
// Trích từ include/ceres/jet.h, dòng 731–745 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> hypot(const Jet<T, N>& x,
                       const Jet<T, N>& y,
                       const Jet<T, N>& z) {
  // d/da sqrt(a) = 0.5 / sqrt(a)
  // d/dx x^2 + y^2 + z^2 = 2x
  // So by the chain rule:
  // d/dx sqrt(x^2 + y^2 + z^2)
  //    = 0.5 / sqrt(x^2 + y^2 + z^2) * 2x
  //    = x / sqrt(x^2 + y^2 + z^2)
  // d/dy sqrt(x^2 + y^2 + z^2) = y / sqrt(x^2 + y^2 + z^2)
  // d/dz sqrt(x^2 + y^2 + z^2) = z / sqrt(x^2 + y^2 + z^2)
  const T tmp = hypot(x.a, y.a, z.a);
  return Jet<T, N>(tmp, x.a / tmp * x.v + y.a / tmp * y.v + z.a / tmp * z.v);
}

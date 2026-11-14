// u0148 – ceres::atan2
// Trích từ include/ceres/jet.h, dòng 1130–1139 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> atan2(const Jet<T, N>& g, const Jet<T, N>& f) {
  // Note order of arguments:
  //
  //   f = a + da
  //   g = b + db

  T const tmp = T(1.0) / (f.a * f.a + g.a * g.a);
  return Jet<T, N>(atan2(g.a, f.a), tmp * (-g.a * f.v + f.a * g.v));
}

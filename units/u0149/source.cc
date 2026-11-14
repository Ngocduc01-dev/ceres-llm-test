// u0149 – ceres::norm
// Trích từ include/ceres/jet.h, dòng 1152–1155 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> norm(const Jet<T, N>& f) {
  return Jet<T, N>(norm(f.a), T(2) * f.a * f.v);
}

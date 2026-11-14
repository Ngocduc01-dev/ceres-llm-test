// u0117 – ceres::ceil
// Trích từ include/ceres/jet.h, dòng 683–686 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> ceil(const Jet<T, N>& f) {
  return Jet<T, N>(ceil(f.a));
}

// u0083 – ceres::operator-
// Trích từ include/ceres/jet.h, dòng 342–345 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> operator-(T s, const Jet<T, N>& f) {
  return Jet<T, N>(s - f.a, -f.v);
}

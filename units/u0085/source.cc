// u0085 – ceres::operator*
// Trích từ include/ceres/jet.h, dòng 354–357 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> operator*(const Jet<T, N>& f, T s) {
  return Jet<T, N>(f.a * s, f.v * s);
}

// u0081 – ceres::operator-
// Trích từ include/ceres/jet.h, dòng 330–333 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> operator-(const Jet<T, N>& f, const Jet<T, N>& g) {
  return Jet<T, N>(f.a - g.a, f.v - g.v);
}

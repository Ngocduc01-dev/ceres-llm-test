// u0077 – ceres::operator-
// Trích từ include/ceres/jet.h, dòng 306–309 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> operator-(const Jet<T, N>& f) {
  return Jet<T, N>(-f.a, -f.v);
}

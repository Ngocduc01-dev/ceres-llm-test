// u0079 – ceres::operator+
// Trích từ include/ceres/jet.h, dòng 318–321 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> operator+(const Jet<T, N>& f, T s) {
  return Jet<T, N>(f.a + s, f.v);
}

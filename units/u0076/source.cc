// u0076 – ceres::operator+
// Trích từ include/ceres/jet.h, dòng 297–300 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> const& operator+(const Jet<T, N>& f) {
  return f;
}

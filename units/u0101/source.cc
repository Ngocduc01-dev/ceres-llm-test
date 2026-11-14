// u0101 – ceres::log
// Trích từ include/ceres/jet.h, dòng 565–569 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> log(const Jet<T, N>& f) {
  const T a_inverse = T(1.0) / f.a;
  return Jet<T, N>(log(f.a), f.v * a_inverse);
}

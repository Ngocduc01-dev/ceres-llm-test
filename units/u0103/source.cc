// u0103 – ceres::log1p
// Trích từ include/ceres/jet.h, dòng 580–584 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> log1p(const Jet<T, N>& f) {
  const T a_inverse = T(1.0) / (T(1.0) + f.a);
  return Jet<T, N>(log1p(f.a), f.v * a_inverse);
}

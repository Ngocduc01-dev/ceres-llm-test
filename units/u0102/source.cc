// u0102 – ceres::log10
// Trích từ include/ceres/jet.h, dòng 572–577 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> log10(const Jet<T, N>& f) {
  // Most compilers will expand log(10) to a constant.
  const T a_inverse = T(1.0) / (f.a * log(T(10.0)));
  return Jet<T, N>(log10(f.a), f.v * a_inverse);
}

// u0120 – ceres::log2
// Trích từ include/ceres/jet.h, dòng 706–710 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> log2(const Jet<T, N>& f) {
  const T derivative = T(1.0) / (f.a * log(T(2)));
  return Jet<T, N>(log2(f.a), f.v * derivative);
}

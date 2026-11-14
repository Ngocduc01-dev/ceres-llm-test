// u0150 – ceres::pow
// Trích từ include/ceres/jet.h, dòng 1159–1163 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> pow(const Jet<T, N>& f, double g) {
  T const tmp = g * pow(f.a, g - T(1.0));
  return Jet<T, N>(pow(f.a, g), tmp * f.v);
}

// u0107 – ceres::cos
// Trích từ include/ceres/jet.h, dòng 610–613 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> cos(const Jet<T, N>& f) {
  return Jet<T, N>(cos(f.a), -sin(f.a) * f.v);
}

// u0133 – ceres::isinf
// Trích từ include/ceres/jet.h, dòng 946–949 (chỉ để xem, không compile)

template <typename T, int N>
inline bool isinf(const Jet<T, N>& f) {
  return isinf(f.a);
}

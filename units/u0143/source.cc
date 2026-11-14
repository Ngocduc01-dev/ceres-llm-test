// u0143 – ceres::signbit
// Trích từ include/ceres/jet.h, dòng 1042–1045 (chỉ để xem, không compile)

template <typename T, int N>
inline bool signbit(const Jet<T, N>& f) {
  return signbit(f.a);
}

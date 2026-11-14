// u0135 – ceres::isnormal
// Trích từ include/ceres/jet.h, dòng 959–962 (chỉ để xem, không compile)

template <typename T, int N>
inline bool isnormal(const Jet<T, N>& f) {
  return isnormal(f.a);
}

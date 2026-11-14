// u0134 – ceres::isnan
// Trích từ include/ceres/jet.h, dòng 952–955 (chỉ để xem, không compile)

template <typename T, int N>
inline bool isnan(const Jet<T, N>& f) {
  return isnan(f.a);
}

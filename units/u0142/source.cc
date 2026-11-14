// u0142 – ceres::fpclassify
// Trích từ include/ceres/jet.h, dòng 1036–1039 (chỉ để xem, không compile)

template <typename T, int N>
inline int fpclassify(const Jet<T, N>& f) {
  return fpclassify(f.a);
}

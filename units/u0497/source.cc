// u0497 – ceres::operator<<
// Trích từ include/ceres/jet.h, dòng 1278–1289 (chỉ để xem, không compile)

template <typename T, int N>
inline std::ostream& operator<<(std::ostream& s, const Jet<T, N>& z) {
  s << "[" << z.a << " ; ";
  for (int i = 0; i < N; ++i) {
    s << z.v[i];
    if (i != N - 1) {
      s << ", ";
    }
  }
  s << "]";
  return s;
}

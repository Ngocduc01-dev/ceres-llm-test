// u0131 – ceres::BesselJn
// Trích từ include/ceres/jet.h, dòng 915–920 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> BesselJn(int n, const Jet<T, N>& f) {
  return Jet<T, N>(
      BesselJn(n, f.a),
      T(0.5) * (BesselJn(n - 1, f.a) - BesselJn(n + 1, f.a)) * f.v);
}

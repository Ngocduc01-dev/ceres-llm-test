// u0129 – ceres::BesselJ0
// Trích từ include/ceres/jet.h, dòng 900–903 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> BesselJ0(const Jet<T, N>& f) {
  return Jet<T, N>(BesselJ0(f.a), -BesselJ1(f.a) * f.v);
}

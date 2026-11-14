// u0130 – ceres::BesselJ1
// Trích từ include/ceres/jet.h, dòng 907–911 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> BesselJ1(const Jet<T, N>& f) {
  return Jet<T, N>(BesselJ1(f.a),
                   T(0.5) * (BesselJ0(f.a) - BesselJn(2, f.a)) * f.v);
}

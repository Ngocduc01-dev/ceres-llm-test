// u0125 – ceres::erfc
// Trích từ include/ceres/jet.h, dòng 863–868 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> erfc(const Jet<T, N>& x) {
  // See in erf() above for the evaluation of the constant in the derivative.
  return Jet<T, N>(erfc(x.a),
                   -x.v * exp(-x.a * x.a) * (T(1) / sqrt(atan(T(1)))));
}

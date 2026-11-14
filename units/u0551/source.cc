// u0551 – ceres::pow
// Trích từ include/ceres/jet.h, dòng 1176–1200 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> pow(T f, const Jet<T, N>& g) {
  Jet<T, N> result;

  if (fpclassify(f) == FP_ZERO && g > 0) {
    // Handle case 2.
    result = Jet<T, N>(T(0.0));
  } else {
    if (f < 0 && g == floor(g.a)) {  // Handle case 3.
      result = Jet<T, N>(pow(f, g.a));
      for (int i = 0; i < N; i++) {
        if (fpclassify(g.v[i]) != FP_ZERO) {
          // Return a NaN when g.v != 0.
          result.v[i] = std::numeric_limits<T>::quiet_NaN();
        }
      }
    } else {
      // Handle case 1.
      T const tmp = pow(f, g.a);
      result = Jet<T, N>(tmp, log(f) * tmp * g.v);
    }
  }

  return result;
}

// u0555 – ceres::pow
// Trích từ include/ceres/jet.h, dòng 1238–1273 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> pow(const Jet<T, N>& f, const Jet<T, N>& g) {
  Jet<T, N> result;

  if (fpclassify(f) == FP_ZERO && g >= 1) {
    // Handle cases 2 and 3.
    if (g > 1) {
      result = Jet<T, N>(T(0.0));
    } else {
      result = f;
    }

  } else {
    if (f < 0 && g == floor(g.a)) {
      // Handle cases 7 and 8.
      T const tmp = g.a * pow(f.a, g.a - T(1.0));
      result = Jet<T, N>(pow(f.a, g.a), tmp * f.v);
      for (int i = 0; i < N; i++) {
        if (fpclassify(g.v[i]) != FP_ZERO) {
          // Return a NaN when g.v != 0.
          result.v[i] = T(std::numeric_limits<double>::quiet_NaN());
        }
      }
    } else {
      // Handle the remaining cases. For cases 4,5,6,9 we allow the log()
      // function to generate -HUGE_VAL or NaN, since those cases result in a
      // nonfinite derivative.
      T const tmp1 = pow(f.a, g.a);
      T const tmp2 = g.a * pow(f.a, g.a - T(1.0));
      T const tmp3 = tmp1 * log(f.a);
      result = Jet<T, N>(tmp1, tmp2 * f.v + tmp3 * g.v);
    }
  }

  return result;
}

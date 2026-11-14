// u0124 – ceres::erf
// Trích từ include/ceres/jet.h, dòng 849–859 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> erf(const Jet<T, N>& x) {
  // We evaluate the constant as follows:
  //   2 / sqrt(pi) = 1 / sqrt(atan(1.))
  // On POSIX systems it is defined as M_2_SQRTPI, but this is not
  // portable and the type may not be T.  The above expression
  // evaluates to full precision with IEEE arithmetic and, since it's
  // constant, the compiler can generate exactly the same code.  gcc
  // does so even at -O0.
  return Jet<T, N>(erf(x.a), x.v * exp(-x.a * x.a) * (T(1) / sqrt(atan(T(1)))));
}

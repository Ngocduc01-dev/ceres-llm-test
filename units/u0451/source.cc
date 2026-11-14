// u0451 – ceres::copysign
// Trích từ include/ceres/jet.h, dòng 549–562 (chỉ để xem, không compile)

template <typename T, int N>
inline Jet<T, N> copysign(const Jet<T, N>& f, const Jet<T, N> g) {
  // The Dirac delta function  δ(b) is undefined at b=0 (here it's
  // infinite) and 0 everywhere else.
  T d = fpclassify(g) == FP_ZERO ? std::numeric_limits<T>::infinity() : T(0);
  T sa = copysign(T(1), f.a);  // sgn(a)
  T sb = copysign(T(1), g.a);  // sgn(b)
  // The second part of the infinitesimal is 2|a|δ(b) which is either infinity
  // or 0 unless a or any of the values of the b infinitesimal are 0. In the
  // latter case, the corresponding values become NaNs (multiplying 0 by
  // infinity gives NaN). We drop the constant factor 2 since it does not change
  // the result (its values will still be either 0, infinity or NaN).
  return Jet<T, N>(copysign(f.a, g.a), sa * sb * f.v + abs(f.a) * d * g.v);
}

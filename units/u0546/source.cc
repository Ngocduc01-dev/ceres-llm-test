// u0546 – ceres::fmax
// Trích từ include/ceres/jet.h, dòng 789–805 (chỉ để xem, không compile)

template <typename Lhs,
          typename Rhs,
          std::enable_if_t<CompatibleJetOperands_v<Lhs, Rhs>>* = nullptr>
inline decltype(auto) fmax(const Lhs& x, const Rhs& y) {
  using J = std::common_type_t<Lhs, Rhs>;
  // As x == y may set FP exceptions in the presence of NaNs when used with
  // non-default compiler options so we avoid its use here.
  if (isnan(x) || isnan(y) || islessgreater(x, y)) {
    return isnan(x) || isless(x, y) ? J{y} : J{x};
  }
  // x == y (scalar parts) return the average of their Jet representations.
#if defined(CERES_HAS_CPP20)
  return midpoint(J{x}, J{y});
#else
  return (J{x} + J{y}) * typename J::Scalar(0.5);
#endif  // defined(CERES_HAS_CPP20)
}

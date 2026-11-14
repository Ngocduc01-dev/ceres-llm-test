// u0518 – ceres::fdim
// Trích từ include/ceres/jet.h, dòng 835–844 (chỉ để xem, không compile)

template <typename Lhs,
          typename Rhs,
          std::enable_if_t<CompatibleJetOperands_v<Lhs, Rhs>>* = nullptr>
inline decltype(auto) fdim(const Lhs& f, const Rhs& g) {
  using J = std::common_type_t<Lhs, Rhs>;
  if (isnan(f) || isnan(g)) {
    return std::numeric_limits<J>::quiet_NaN();
  }
  return isgreater(f, g) ? J{f - g} : J{};
}

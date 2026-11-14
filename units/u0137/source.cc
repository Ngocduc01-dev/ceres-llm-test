// u0137 – ceres::isgreater
// Trích từ include/ceres/jet.h, dòng 980–986 (chỉ để xem, không compile)

template <typename Lhs,
          typename Rhs,
          std::enable_if_t<CompatibleJetOperands_v<Lhs, Rhs>>* = nullptr>
inline bool isgreater(const Lhs& f, const Rhs& g) {
  using internal::AsScalar;
  return isgreater(AsScalar(f), AsScalar(g));
}

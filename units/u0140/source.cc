// u0140 – ceres::isgreaterequal
// Trích từ include/ceres/jet.h, dòng 1016–1022 (chỉ để xem, không compile)

template <typename Lhs,
          typename Rhs,
          std::enable_if_t<CompatibleJetOperands_v<Lhs, Rhs>>* = nullptr>
inline bool isgreaterequal(const Lhs& f, const Rhs& g) {
  using internal::AsScalar;
  return isgreaterequal(AsScalar(f), AsScalar(g));
}

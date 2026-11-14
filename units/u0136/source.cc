// u0136 – ceres::isless
// Trích từ include/ceres/jet.h, dòng 968–974 (chỉ để xem, không compile)

template <typename Lhs,
          typename Rhs,
          std::enable_if_t<CompatibleJetOperands_v<Lhs, Rhs>>* = nullptr>
inline bool isless(const Lhs& f, const Rhs& g) {
  using internal::AsScalar;
  return isless(AsScalar(f), AsScalar(g));
}

// u0139 – ceres::islessgreater
// Trích từ include/ceres/jet.h, dòng 1004–1010 (chỉ để xem, không compile)

template <typename Lhs,
          typename Rhs,
          std::enable_if_t<CompatibleJetOperands_v<Lhs, Rhs>>* = nullptr>
inline bool islessgreater(const Lhs& f, const Rhs& g) {
  using internal::AsScalar;
  return islessgreater(AsScalar(f), AsScalar(g));
}

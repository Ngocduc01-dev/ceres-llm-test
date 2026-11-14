// u0141 – ceres::isunordered
// Trích từ include/ceres/jet.h, dòng 1026–1032 (chỉ để xem, không compile)

template <typename Lhs,
          typename Rhs,
          std::enable_if_t<CompatibleJetOperands_v<Lhs, Rhs>>* = nullptr>
inline bool isunordered(const Lhs& f, const Rhs& g) {
  using internal::AsScalar;
  return isunordered(AsScalar(f), AsScalar(g));
}

// u0138 – ceres::islessequal
// Trích từ include/ceres/jet.h, dòng 992–998 (chỉ để xem, không compile)

template <typename Lhs,
          typename Rhs,
          std::enable_if_t<CompatibleJetOperands_v<Lhs, Rhs>>* = nullptr>
inline bool islessequal(const Lhs& f, const Rhs& g) {
  using internal::AsScalar;
  return islessequal(AsScalar(f), AsScalar(g));
}

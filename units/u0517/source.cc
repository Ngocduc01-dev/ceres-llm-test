// u0517 – ceres::internal::ComputeSphereManifoldMinus
// Trích từ include/ceres/internal/sphere_manifold_functions.h, dòng 109–131 (chỉ để xem, không compile)

template <typename VT, typename XT, typename YT, typename YMinusXT>
inline void ComputeSphereManifoldMinus(
    const VT& v, double beta, const XT& x, const YT& y, YMinusXT* y_minus_x) {
  constexpr int AmbientSpaceDim = VT::RowsAtCompileTime;
  constexpr int TangentSpaceDim =
      AmbientSpaceDim == Eigen::Dynamic ? Eigen::Dynamic : AmbientSpaceDim - 1;
  using AmbientVector = Eigen::Matrix<double, AmbientSpaceDim, 1>;

  const int tangent_size = v.size() - 1;

  const AmbientVector hy = ApplyHouseholderVector(y, v, beta) / x.norm();

  // Calculate y - x. See B.2 p.25 equation (108).
  const double y_last = hy[tangent_size];
  const double hy_norm = hy.template head<TangentSpaceDim>(tangent_size).norm();
  if (hy_norm == 0.0) {
    y_minus_x->setZero();
    y_minus_x->data()[tangent_size - 1] = y_last >= 0 ? 0.0 : constants::pi;
  } else {
    *y_minus_x = std::atan2(hy_norm, y_last) / hy_norm *
                 hy.template head<TangentSpaceDim>(tangent_size);
  }
}

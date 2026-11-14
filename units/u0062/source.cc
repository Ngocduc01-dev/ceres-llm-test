// u0062 – ceres::internal::ComputeSphereManifoldPlus
// Trích từ include/ceres/internal/sphere_manifold_functions.h, dòng 64–82 (chỉ để xem, không compile)

template <typename VT, typename XT, typename DeltaT, typename XPlusDeltaT>
inline void ComputeSphereManifoldPlus(const VT& v,
                                      double beta,
                                      const XT& x,
                                      const DeltaT& delta,
                                      const double norm_delta,
                                      XPlusDeltaT* x_plus_delta) {
  constexpr int AmbientDim = VT::RowsAtCompileTime;

  // Map the delta from the minimum representation to the over parameterized
  // homogeneous vector. See B.2 p.25 equation (106) - (107) for more details.
  const double sin_delta_by_delta = std::sin(norm_delta) / norm_delta;

  Eigen::Matrix<double, AmbientDim, 1> y(v.size());
  y << sin_delta_by_delta * delta, std::cos(norm_delta);

  // Apply the delta update to remain on the sphere.
  *x_plus_delta = x.norm() * ApplyHouseholderVector(y, v, beta);
}

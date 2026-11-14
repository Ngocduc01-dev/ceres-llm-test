// u0463 – ceres::SphereManifold::Plus
// Trích từ include/ceres/sphere_manifold.h, dòng 156–186 (chỉ để xem, không compile)

template <int AmbientSpaceDimension>
bool SphereManifold<AmbientSpaceDimension>::Plus(
    const double* x_ptr,
    const double* delta_ptr,
    double* x_plus_delta_ptr) const {
  Eigen::Map<const AmbientVector> x(x_ptr, size_);
  Eigen::Map<const TangentVector> delta(delta_ptr, size_ - 1);
  Eigen::Map<AmbientVector> x_plus_delta(x_plus_delta_ptr, size_);

  const double norm_delta = delta.norm();

  if (norm_delta == 0.0) {
    x_plus_delta = x;
    return true;
  }

  AmbientVector v(size_);
  double beta;

  // NOTE: The explicit template arguments are needed here because
  // ComputeHouseholderVector is templated and some versions of MSVC
  // have trouble deducing the type of v automatically.
  internal::ComputeHouseholderVector<Eigen::Map<const AmbientVector>,
                                     double,
                                     AmbientSpaceDimension>(x, &v, &beta);

  internal::ComputeSphereManifoldPlus(
      v, beta, x, delta, norm_delta, &x_plus_delta);

  return true;
}

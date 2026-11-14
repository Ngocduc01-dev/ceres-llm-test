// u0216 – ceres::SphereManifold::Minus
// Trích từ include/ceres/sphere_manifold.h, dòng 198–218 (chỉ để xem, không compile)

template <int AmbientSpaceDimension>
bool SphereManifold<AmbientSpaceDimension>::Minus(const double* y_ptr,
                                                  const double* x_ptr,
                                                  double* y_minus_x_ptr) const {
  AmbientVector y = Eigen::Map<const AmbientVector>(y_ptr, size_);
  Eigen::Map<const AmbientVector> x(x_ptr, size_);
  Eigen::Map<TangentVector> y_minus_x(y_minus_x_ptr, size_ - 1);

  // Apply hoseholder transformation.
  AmbientVector v(size_);
  double beta;

  // NOTE: The explicit template arguments are needed here because
  // ComputeHouseholderVector is templated and some versions of MSVC
  // have trouble deducing the type of v automatically.
  internal::ComputeHouseholderVector<Eigen::Map<const AmbientVector>,
                                     double,
                                     AmbientSpaceDimension>(x, &v, &beta);
  internal::ComputeSphereManifoldMinus(v, beta, x, y, &y_minus_x);
  return true;
}

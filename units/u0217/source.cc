// u0217 – ceres::SphereManifold::MinusJacobian
// Trích từ include/ceres/sphere_manifold.h, dòng 220–228 (chỉ để xem, không compile)

template <int AmbientSpaceDimension>
bool SphereManifold<AmbientSpaceDimension>::MinusJacobian(
    const double* x_ptr, double* jacobian_ptr) const {
  Eigen::Map<const AmbientVector> x(x_ptr, size_);
  Eigen::Map<MatrixMinusJacobian> jacobian(jacobian_ptr, size_ - 1, size_);

  internal::ComputeSphereManifoldMinusJacobian(x, &jacobian);
  return true;
}

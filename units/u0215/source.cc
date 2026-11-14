// u0215 – ceres::SphereManifold::PlusJacobian
// Trích từ include/ceres/sphere_manifold.h, dòng 188–196 (chỉ để xem, không compile)

template <int AmbientSpaceDimension>
bool SphereManifold<AmbientSpaceDimension>::PlusJacobian(
    const double* x_ptr, double* jacobian_ptr) const {
  Eigen::Map<const AmbientVector> x(x_ptr, size_);
  Eigen::Map<MatrixPlusJacobian> jacobian(jacobian_ptr, size_, size_ - 1);
  internal::ComputeSphereManifoldPlusJacobian(x, &jacobian);

  return true;
}

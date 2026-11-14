// u0169 – ceres::LineManifold::PlusJacobian
// Trích từ include/ceres/line_manifold.h, dòng 218–238 (chỉ để xem, không compile)

template <int AmbientSpaceDimension>
bool LineManifold<AmbientSpaceDimension>::PlusJacobian(
    const double* x_ptr, double* jacobian_ptr) const {
  Eigen::Map<const AmbientVector> d(x_ptr + size_, size_);
  Eigen::Map<MatrixPlusJacobian> jacobian(
      jacobian_ptr, 2 * size_, 2 * (size_ - 1));

  // Clear the Jacobian as only half of the matrix is not zero.
  jacobian.setZero();

  auto jacobian_d =
      jacobian
          .template topLeftCorner<AmbientSpaceDimension, TangentSpaceDimension>(
              size_, size_ - 1);
  auto jacobian_o = jacobian.template bottomRightCorner<AmbientSpaceDimension,
                                                        TangentSpaceDimension>(
      size_, size_ - 1);
  internal::ComputeSphereManifoldPlusJacobian(d, &jacobian_d);
  jacobian_o = jacobian_d;
  return true;
}

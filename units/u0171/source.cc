// u0171 – ceres::LineManifold::MinusJacobian
// Trích từ include/ceres/line_manifold.h, dòng 272–293 (chỉ để xem, không compile)

template <int AmbientSpaceDimension>
bool LineManifold<AmbientSpaceDimension>::MinusJacobian(
    const double* x_ptr, double* jacobian_ptr) const {
  Eigen::Map<const AmbientVector> d(x_ptr + size_, size_);
  Eigen::Map<MatrixMinusJacobian> jacobian(
      jacobian_ptr, 2 * (size_ - 1), 2 * size_);

  // Clear the Jacobian as only half of the matrix is not zero.
  jacobian.setZero();

  auto jacobian_d =
      jacobian
          .template topLeftCorner<TangentSpaceDimension, AmbientSpaceDimension>(
              size_ - 1, size_);
  auto jacobian_o = jacobian.template bottomRightCorner<TangentSpaceDimension,
                                                        AmbientSpaceDimension>(
      size_ - 1, size_);
  internal::ComputeSphereManifoldMinusJacobian(d, &jacobian_d);
  jacobian_o = jacobian_d;

  return true;
}

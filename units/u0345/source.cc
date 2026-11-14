// u0345 – ceres::QuaternionManifold::MinusJacobian
// Trích từ internal/ceres/manifold.cc, dòng 284–288 (chỉ để xem, không compile)

bool QuaternionManifold::MinusJacobian(const double* x,
                                       double* jacobian) const {
  QuaternionMinusJacobianImpl<CeresQuaternionOrder>(x, jacobian);
  return true;
}

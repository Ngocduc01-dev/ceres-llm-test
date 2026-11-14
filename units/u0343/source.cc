// u0343 – ceres::QuaternionManifold::PlusJacobian
// Trích từ internal/ceres/manifold.cc, dòng 272–275 (chỉ để xem, không compile)

bool QuaternionManifold::PlusJacobian(const double* x, double* jacobian) const {
  QuaternionPlusJacobianImpl<CeresQuaternionOrder>(x, jacobian);
  return true;
}

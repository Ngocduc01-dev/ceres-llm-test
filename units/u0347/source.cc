// u0347 – ceres::EigenQuaternionManifold::PlusJacobian
// Trích từ internal/ceres/manifold.cc, dòng 297–301 (chỉ để xem, không compile)

bool EigenQuaternionManifold::PlusJacobian(const double* x,
                                           double* jacobian) const {
  QuaternionPlusJacobianImpl<EigenQuaternionOrder>(x, jacobian);
  return true;
}

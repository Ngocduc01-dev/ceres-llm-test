// u0349 – ceres::EigenQuaternionManifold::MinusJacobian
// Trích từ internal/ceres/manifold.cc, dòng 310–314 (chỉ để xem, không compile)

bool EigenQuaternionManifold::MinusJacobian(const double* x,
                                            double* jacobian) const {
  QuaternionMinusJacobianImpl<EigenQuaternionOrder>(x, jacobian);
  return true;
}

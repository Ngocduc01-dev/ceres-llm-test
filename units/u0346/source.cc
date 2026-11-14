// u0346 – ceres::EigenQuaternionManifold::Plus
// Trích từ internal/ceres/manifold.cc, dòng 290–295 (chỉ để xem, không compile)

bool EigenQuaternionManifold::Plus(const double* x,
                                   const double* delta,
                                   double* x_plus_delta) const {
  QuaternionPlusImpl<EigenQuaternionOrder>(x, delta, x_plus_delta);
  return true;
}

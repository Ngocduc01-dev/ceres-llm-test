// u0342 – ceres::QuaternionManifold::Plus
// Trích từ internal/ceres/manifold.cc, dòng 265–270 (chỉ để xem, không compile)

bool QuaternionManifold::Plus(const double* x,
                              const double* delta,
                              double* x_plus_delta) const {
  QuaternionPlusImpl<CeresQuaternionOrder>(x, delta, x_plus_delta);
  return true;
}

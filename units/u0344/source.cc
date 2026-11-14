// u0344 – ceres::QuaternionManifold::Minus
// Trích từ internal/ceres/manifold.cc, dòng 277–282 (chỉ để xem, không compile)

bool QuaternionManifold::Minus(const double* y,
                               const double* x,
                               double* y_minus_x) const {
  QuaternionMinusImpl<CeresQuaternionOrder>(y, x, y_minus_x);
  return true;
}

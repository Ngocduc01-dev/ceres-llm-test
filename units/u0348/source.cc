// u0348 – ceres::EigenQuaternionManifold::Minus
// Trích từ internal/ceres/manifold.cc, dòng 303–308 (chỉ để xem, không compile)

bool EigenQuaternionManifold::Minus(const double* y,
                                    const double* x,
                                    double* y_minus_x) const {
  QuaternionMinusImpl<EigenQuaternionOrder>(y, x, y_minus_x);
  return true;
}

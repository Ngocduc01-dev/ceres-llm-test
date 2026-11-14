// u0183 – ceres::EuclideanManifold::Minus
// Trích từ include/ceres/manifold.h, dòng 292–300 (chỉ để xem, không compile)

  bool Minus(const double* y_ptr,
             const double* x_ptr,
             double* y_minus_x_ptr) const override {
    Eigen::Map<const AmbientVector> x(x_ptr, size_);
    Eigen::Map<const AmbientVector> y(y_ptr, size_);
    Eigen::Map<AmbientVector> y_minus_x(y_minus_x_ptr, size_);
    y_minus_x = y - x;
    return true;
  }

// u0180 – ceres::EuclideanManifold::Plus
// Trích từ include/ceres/manifold.h, dòng 268–276 (chỉ để xem, không compile)

  bool Plus(const double* x_ptr,
            const double* delta_ptr,
            double* x_plus_delta_ptr) const override {
    Eigen::Map<const AmbientVector> x(x_ptr, size_);
    Eigen::Map<const AmbientVector> delta(delta_ptr, size_);
    Eigen::Map<AmbientVector> x_plus_delta(x_plus_delta_ptr, size_);
    x_plus_delta = x + delta;
    return true;
  }

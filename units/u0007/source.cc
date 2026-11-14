// u0007 – ceres::AutoDiffManifold::Plus
// Trích từ include/ceres/autodiff_manifold.h, dòng 158–162 (chỉ để xem, không compile)

  bool Plus(const double* x,
            const double* delta,
            double* x_plus_delta) const override {
    return functor_->Plus(x, delta, x_plus_delta);
  }

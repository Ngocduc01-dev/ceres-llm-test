// u0008 – ceres::AutoDiffManifold::Minus
// Trích từ include/ceres/autodiff_manifold.h, dòng 166–170 (chỉ để xem, không compile)

  bool Minus(const double* y,
             const double* x,
             double* y_minus_x) const override {
    return functor_->Minus(y, x, y_minus_x);
  }

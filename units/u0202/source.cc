// u0202 – ceres::ProductManifold::Minus
// Trích từ include/ceres/product_manifold.h, dòng 110–115 (chỉ để xem, không compile)

  bool Minus(const double* y,
             const double* x,
             double* y_minus_x) const override {
    return MinusImpl(
        y, x, y_minus_x, std::make_index_sequence<kNumManifolds>{});
  }

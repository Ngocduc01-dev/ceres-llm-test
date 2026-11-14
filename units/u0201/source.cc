// u0201 – ceres::ProductManifold::Plus
// Trích từ include/ceres/product_manifold.h, dòng 103–108 (chỉ để xem, không compile)

  bool Plus(const double* x,
            const double* delta,
            double* x_plus_delta) const override {
    return PlusImpl(
        x, delta, x_plus_delta, std::make_index_sequence<kNumManifolds>{});
  }

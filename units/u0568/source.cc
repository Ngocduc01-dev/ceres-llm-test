// u0568 – ceres::ProductManifold::MinusImpl
// Trích từ include/ceres/product_manifold.h, dòng 192–197 (chỉ để xem, không compile)

  static constexpr bool MinusImpl(const double* /*y*/,
                                  const double* /*x*/,
                                  double* /*y_minus_x*/,
                                  std::index_sequence<>) noexcept {
    return true;
  }

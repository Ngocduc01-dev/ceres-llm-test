// u0567 – ceres::ProductManifold::PlusImpl
// Trích từ include/ceres/product_manifold.h, dòng 170–175 (chỉ để xem, không compile)

  static constexpr bool PlusImpl(const double* /*x*/,
                                 const double* /*delta*/,
                                 double* /*x_plus_delta*/,
                                 std::index_sequence<>) noexcept {
    return true;
  }

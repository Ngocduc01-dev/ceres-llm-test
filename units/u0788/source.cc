// u0788 – ceres::ProductManifold::MinusJacobianImpl
// Trích từ include/ceres/product_manifold.h, dòng 249–255 (chỉ để xem, không compile)

  static constexpr bool MinusJacobianImpl(
      const double* /*x*/,
      MatrixRef& /*jacobian*/,
      internal::FixedArray<double>& /*buffer*/,
      std::index_sequence<>) noexcept {
    return true;
  }

// u0787 – ceres::ProductManifold::PlusJacobianImpl
// Trích từ include/ceres/product_manifold.h, dòng 220–226 (chỉ để xem, không compile)

  static constexpr bool PlusJacobianImpl(
      const double* /*x*/,
      MatrixRef& /*jacobian*/,
      internal::FixedArray<double>& /*buffer*/,
      std::index_sequence<>) noexcept {
    return true;
  }

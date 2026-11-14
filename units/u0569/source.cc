// u0569 – ceres::ProductManifold::Dereference
// Trích từ include/ceres/product_manifold.h, dòng 277–281 (chỉ để xem, không compile)

  template <typename T,
            std::enable_if_t<!IsDereferenceable<T>::value>* = nullptr>
  static constexpr decltype(auto) Dereference(T& value) {
    return value;
  }

// u0589 – ceres::ProductManifold::Dereference
// Trích từ include/ceres/product_manifold.h, dòng 291–295 (chỉ để xem, không compile)

  template <typename T>
  static constexpr decltype(auto) Dereference(T* p) {
    assert(p != nullptr);
    return *p;
  }

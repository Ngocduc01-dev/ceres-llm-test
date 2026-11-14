// u0588 – ceres::ProductManifold::ExclusiveScan
// Trích từ include/ceres/product_manifold.h, dòng 257–268 (chỉ để xem, không compile)

  template <typename T, std::size_t N>
  static std::array<T, N> ExclusiveScan(const std::array<T, N>& values) {
    std::array<T, N> result;
    // TODO Replace with std::exclusive_scan once all platforms have full C++17
    // STL support.
    T init = 0;
    for (std::size_t i = 0; i != N; ++i) {
      result[i] = init;
      init += values[i];
    }
    return result;
  }

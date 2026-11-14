// u0155 – ?::std::numeric_limits::infinity
// Trích từ include/ceres/jet.h, dòng 1342–1344 (chỉ để xem, không compile)

  static constexpr ceres::Jet<T, N> infinity() noexcept {
    return ceres::Jet<T, N>(std::numeric_limits<T>::infinity());
  }

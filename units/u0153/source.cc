// u0153 – ?::std::numeric_limits::epsilon
// Trích từ include/ceres/jet.h, dòng 1336–1338 (chỉ để xem, không compile)

  static constexpr ceres::Jet<T, N> epsilon() noexcept {
    return ceres::Jet<T, N>(std::numeric_limits<T>::epsilon());
  }

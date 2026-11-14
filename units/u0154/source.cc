// u0154 – ?::std::numeric_limits::round_error
// Trích từ include/ceres/jet.h, dòng 1339–1341 (chỉ để xem, không compile)

  static constexpr ceres::Jet<T, N> round_error() noexcept {
    return ceres::Jet<T, N>(std::numeric_limits<T>::round_error());
  }

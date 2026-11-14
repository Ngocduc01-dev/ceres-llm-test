// u0157 – ?::std::numeric_limits::signaling_NaN
// Trích từ include/ceres/jet.h, dòng 1348–1350 (chỉ để xem, không compile)

  static constexpr ceres::Jet<T, N> signaling_NaN() noexcept {
    return ceres::Jet<T, N>(std::numeric_limits<T>::signaling_NaN());
  }

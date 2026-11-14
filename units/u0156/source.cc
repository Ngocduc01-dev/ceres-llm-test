// u0156 – ?::std::numeric_limits::quiet_NaN
// Trích từ include/ceres/jet.h, dòng 1345–1347 (chỉ để xem, không compile)

  static constexpr ceres::Jet<T, N> quiet_NaN() noexcept {
    return ceres::Jet<T, N>(std::numeric_limits<T>::quiet_NaN());
  }

// u0158 – ?::std::numeric_limits::denorm_min
// Trích từ include/ceres/jet.h, dòng 1351–1353 (chỉ để xem, không compile)

  static constexpr ceres::Jet<T, N> denorm_min() noexcept {
    return ceres::Jet<T, N>(std::numeric_limits<T>::denorm_min());
  }

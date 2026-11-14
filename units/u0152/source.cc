// u0152 – ?::std::numeric_limits::lowest
// Trích từ include/ceres/jet.h, dòng 1333–1335 (chỉ để xem, không compile)

  static constexpr ceres::Jet<T, N> lowest() noexcept {
    return ceres::Jet<T, N>(std::numeric_limits<T>::lowest());
  }

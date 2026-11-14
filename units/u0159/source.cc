// u0159 – ?::std::numeric_limits::max
// Trích từ include/ceres/jet.h, dòng 1355–1358 (chỉ để xem, không compile)

  static constexpr ceres::Jet<T, N> max
  CERES_PREVENT_MACRO_SUBSTITUTION() noexcept {
    return ceres::Jet<T, N>((std::numeric_limits<T>::max)());
  }

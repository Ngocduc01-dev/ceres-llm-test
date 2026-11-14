// u0151 – ?::std::numeric_limits::min
// Trích từ include/ceres/jet.h, dòng 1329–1332 (chỉ để xem, không compile)

  static constexpr ceres::Jet<T, N> min
  CERES_PREVENT_MACRO_SUBSTITUTION() noexcept {
    return ceres::Jet<T, N>((std::numeric_limits<T>::min)());
  }

// u0161 – Eigen::NumTraits::epsilon
// Trích từ include/ceres/jet.h, dòng 1378–1380 (chỉ để xem, không compile)

  static inline Real epsilon() {
    return Real(std::numeric_limits<T>::epsilon());
  }

// u0165 – Eigen::NumTraits::lowest
// Trích từ include/ceres/jet.h, dòng 1413–1413 (chỉ để xem, không compile)

  static inline Real lowest() { return Real(-(std::numeric_limits<T>::max)()); }

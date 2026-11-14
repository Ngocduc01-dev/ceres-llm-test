// u0160 – Eigen::NumTraits::dummy_precision
// Trích từ include/ceres/jet.h, dòng 1374–1376 (chỉ để xem, không compile)

  static typename ceres::Jet<T, N> dummy_precision() {
    return ceres::Jet<T, N>(1e-12);
  }

// u0070 – ceres::Jet::Jet<T, N>
// Trích từ include/ceres/jet.h, dòng 229–233 (chỉ để xem, không compile)

  Jet(const T& value, int k) {
    a = value;
    v.setConstant(Scalar());
    v[k] = T(1.0);
  }

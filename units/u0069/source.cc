// u0069 – ceres::Jet::Jet<T, N>
// Trích từ include/ceres/jet.h, dòng 223–226 (chỉ để xem, không compile)

  explicit Jet(const T& value) {
    a = value;
    v.setConstant(Scalar());
  }

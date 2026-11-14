// u0684 – ceres::internal::LinearOperator::LeftMultiplyAndAccumulate
// Trích từ internal/ceres/linear_operator.h, dòng 67–69 (chỉ để xem, không compile)

  virtual void LeftMultiplyAndAccumulate(const Vector& x, Vector& y) const {
    LeftMultiplyAndAccumulate(x.data(), y.data());
  }

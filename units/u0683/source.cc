// u0683 – ceres::internal::LinearOperator::RightMultiplyAndAccumulate
// Trích từ internal/ceres/linear_operator.h, dòng 63–65 (chỉ để xem, không compile)

  virtual void RightMultiplyAndAccumulate(const Vector& x, Vector& y) const {
    RightMultiplyAndAccumulate(x.data(), y.data());
  }

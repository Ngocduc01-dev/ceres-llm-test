// u1154 – ceres::internal::LinearOperator::LeftMultiplyAndAccumulate
// Trích từ internal/ceres/linear_operator.h, dòng 78–83 (chỉ để xem, không compile)

  virtual void LeftMultiplyAndAccumulate(const Vector& x,
                                         Vector& y,
                                         ContextImpl* context,
                                         int num_threads) const {
    LeftMultiplyAndAccumulate(x.data(), y.data(), context, num_threads);
  }

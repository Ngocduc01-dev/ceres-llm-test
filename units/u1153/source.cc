// u1153 – ceres::internal::LinearOperator::RightMultiplyAndAccumulate
// Trích từ internal/ceres/linear_operator.h, dòng 71–76 (chỉ để xem, không compile)

  virtual void RightMultiplyAndAccumulate(const Vector& x,
                                          Vector& y,
                                          ContextImpl* context,
                                          int num_threads) const {
    RightMultiplyAndAccumulate(x.data(), y.data(), context, num_threads);
  }

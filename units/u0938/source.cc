// u0938 – ceres::internal::LinearOperator::LeftMultiplyAndAccumulate
// Trích từ internal/ceres/linear_operator.cc, dòng 49–59 (chỉ để xem, không compile)

void LinearOperator::LeftMultiplyAndAccumulate(const double* x,
                                               double* y,
                                               ContextImpl* context,
                                               int num_threads) const {
  (void)context;
  if (num_threads != 1) {
    VLOG(3) << "Parallel left product is not supported by linear operator "
               "implementation";
  }
  LeftMultiplyAndAccumulate(x, y);
}

// u0937 – ceres::internal::LinearOperator::RightMultiplyAndAccumulate
// Trích từ internal/ceres/linear_operator.cc, dòng 37–47 (chỉ để xem, không compile)

void LinearOperator::RightMultiplyAndAccumulate(const double* x,
                                                double* y,
                                                ContextImpl* context,
                                                int num_threads) const {
  (void)context;
  if (num_threads != 1) {
    VLOG(3) << "Parallel right product is not supported by linear operator "
               "implementation";
  }
  RightMultiplyAndAccumulate(x, y);
}

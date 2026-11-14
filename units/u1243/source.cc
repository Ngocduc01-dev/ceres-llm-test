// u1243 – ceres::internal::BlockCRSJacobiPreconditioner::RightMultiplyAndAccumulate
// Trích từ internal/ceres/block_jacobi_preconditioner.h, dòng 85–87 (chỉ để xem, không compile)

  void RightMultiplyAndAccumulate(const double* x, double* y) const final {
    m_->RightMultiplyAndAccumulate(x, y);
  }

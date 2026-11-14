// u1240 – ceres::internal::BlockSparseJacobiPreconditioner::RightMultiplyAndAccumulate
// Trích từ internal/ceres/block_jacobi_preconditioner.h, dòng 62–64 (chỉ để xem, không compile)

  void RightMultiplyAndAccumulate(const double* x, double* y) const final {
    return m_->RightMultiplyAndAccumulate(x, y);
  }

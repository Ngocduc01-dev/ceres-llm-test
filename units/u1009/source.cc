// u1009 – ceres::internal::LowRankInverseHessian::LeftMultiplyAndAccumulate
// Trích từ internal/ceres/low_rank_inverse_hessian.h, dòng 87–89 (chỉ để xem, không compile)

  void LeftMultiplyAndAccumulate(const double* x, double* y) const final {
    RightMultiplyAndAccumulate(x, y);
  }

// u0385 – ceres::internal::IdentityPreconditioner::RightMultiplyAndAccumulate
// Trích từ internal/ceres/preconditioner.h, dòng 168–170 (chỉ để xem, không compile)

  void RightMultiplyAndAccumulate(const double* x, double* y) const final {
    VectorRef(y, num_rows_) += ConstVectorRef(x, num_rows_);
  }

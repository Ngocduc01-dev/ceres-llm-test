// u1246 – ceres::internal::ImplicitSchurComplement::LeftMultiplyAndAccumulate
// Trích từ internal/ceres/implicit_schur_complement.h, dòng 121–123 (chỉ để xem, không compile)

  void LeftMultiplyAndAccumulate(const double* x, double* y) const final {
    RightMultiplyAndAccumulate(x, y);
  }

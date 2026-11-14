// u0382 – ceres::internal::Preconditioner::LeftMultiplyAndAccumulate
// Trích từ internal/ceres/preconditioner.h, dòng 152–154 (chỉ để xem, không compile)

  void LeftMultiplyAndAccumulate(const double* x, double* y) const override {
    return RightMultiplyAndAccumulate(x, y);
  }

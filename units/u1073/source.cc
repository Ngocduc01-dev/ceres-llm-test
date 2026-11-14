// u1073 – ceres::internal::LinearOperatorAdapter::RightMultiplyAndAccumulate
// Trích từ internal/ceres/conjugate_gradients_solver.h, dòng 69–71 (chỉ để xem, không compile)

  void RightMultiplyAndAccumulate(const Vector& x, Vector& y) final {
    linear_operator_.RightMultiplyAndAccumulate(x, y);
  }

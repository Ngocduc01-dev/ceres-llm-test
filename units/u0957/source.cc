// u0957 – ceres::internal::DoglegStrategy::ComputeGradient
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 175–180 (chỉ để xem, không compile)

void DoglegStrategy::ComputeGradient(SparseMatrix* jacobian,
                                     const double* residuals) {
  gradient_.setZero();
  jacobian->LeftMultiplyAndAccumulate(residuals, gradient_.data());
  gradient_.array() /= diagonal_.array();
}

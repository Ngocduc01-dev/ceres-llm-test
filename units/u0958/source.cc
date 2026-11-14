// u0958 – ceres::internal::DoglegStrategy::ComputeCauchyPoint
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 184–193 (chỉ để xem, không compile)

void DoglegStrategy::ComputeCauchyPoint(SparseMatrix* jacobian) {
  // alpha * -gradient is the Cauchy point.
  Vector Jg(jacobian->num_rows());
  Jg.setZero();
  // The Jacobian is scaled implicitly by computing J * (D^-1 * (D^-1 * g))
  // instead of (J * D^-1) * (D^-1 * g).
  Vector scaled_gradient = (gradient_.array() / diagonal_.array()).matrix();
  jacobian->RightMultiplyAndAccumulate(scaled_gradient.data(), Jg.data());
  alpha_ = gradient_.squaredNorm() / Jg.squaredNorm();
}

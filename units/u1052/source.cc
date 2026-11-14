// u1052 – ceres::NormalPrior::Evaluate
// Trích từ internal/ceres/normal_prior.cc, dòng 51–64 (chỉ để xem, không compile)

bool NormalPrior::Evaluate(double const* const* parameters,
                           double* residuals,
                           double** jacobians) const {
  ConstVectorRef p(parameters[0], parameter_block_sizes()[0]);
  VectorRef r(residuals, num_residuals());
  // The following line should read
  // r = A_ * (p - b_);
  // The extra eval is to get around a bug in the Eigen library.
  r = A_ * (p - b_).eval();
  if ((jacobians != nullptr) && (jacobians[0] != nullptr)) {
    MatrixRef(jacobians[0], num_residuals(), parameter_block_sizes()[0]) = A_;
  }
  return true;
}

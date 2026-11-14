// u0778 – ceres::internal::FindInterpolatingPolynomial
// Trích từ internal/ceres/polynomial.cc, dòng 326–367 (chỉ để xem, không compile)

Vector FindInterpolatingPolynomial(const std::vector<FunctionSample>& samples) {
  const int num_samples = samples.size();
  int num_constraints = 0;
  for (int i = 0; i < num_samples; ++i) {
    if (samples[i].value_is_valid) {
      ++num_constraints;
    }
    if (samples[i].gradient_is_valid) {
      ++num_constraints;
    }
  }

  const int degree = num_constraints - 1;

  Matrix lhs = Matrix::Zero(num_constraints, num_constraints);
  Vector rhs = Vector::Zero(num_constraints);

  int row = 0;
  for (int i = 0; i < num_samples; ++i) {
    const FunctionSample& sample = samples[i];
    if (sample.value_is_valid) {
      for (int j = 0; j <= degree; ++j) {
        lhs(row, j) = pow(sample.x, degree - j);
      }
      rhs(row) = sample.value;
      ++row;
    }

    if (sample.gradient_is_valid) {
      for (int j = 0; j < degree; ++j) {
        lhs(row, j) = (degree - j) * pow(sample.x, degree - j - 1);
      }
      rhs(row) = sample.gradient;
      ++row;
    }
  }

  // TODO(sameeragarwal): This is a hack.
  // https://github.com/ceres-solver/ceres-solver/issues/248
  Eigen::FullPivLU<Matrix> lu(lhs);
  return lu.setThreshold(0.0).solve(rhs);
}

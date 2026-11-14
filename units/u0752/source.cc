// u0752 – ceres::internal::DifferentiatePolynomial
// Trích từ internal/ceres/polynomial.cc, dòng 253–270 (chỉ để xem, không compile)

Vector DifferentiatePolynomial(const Vector& polynomial) {
  const int degree = polynomial.rows() - 1;
  CHECK_GE(degree, 0);

  // Degree zero polynomials are constants, and their derivative does
  // not result in a smaller degree polynomial, just a degree zero
  // polynomial with value zero.
  if (degree == 0) {
    return Eigen::VectorXd::Zero(1);
  }

  Vector derivative(degree);
  for (int i = 0; i < degree; ++i) {
    derivative(i) = (degree - i) * polynomial(i);
  }

  return derivative;
}

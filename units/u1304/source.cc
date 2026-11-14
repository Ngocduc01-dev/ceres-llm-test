// u1304 – ceres::internal::MinimizePolynomial
// Trích từ internal/ceres/polynomial.cc, dòng 272–324 (chỉ để xem, không compile)

void MinimizePolynomial(const Vector& polynomial,
                        const double x_min,
                        const double x_max,
                        double* optimal_x,
                        double* optimal_value) {
  // Find the minimum of the polynomial at the two ends.
  //
  // We start by inspecting the middle of the interval. Technically
  // this is not needed, but we do this to make this code as close to
  // the minFunc package as possible.
  *optimal_x = (x_min + x_max) / 2.0;
  *optimal_value = EvaluatePolynomial(polynomial, *optimal_x);

  const double x_min_value = EvaluatePolynomial(polynomial, x_min);
  if (x_min_value < *optimal_value) {
    *optimal_value = x_min_value;
    *optimal_x = x_min;
  }

  const double x_max_value = EvaluatePolynomial(polynomial, x_max);
  if (x_max_value < *optimal_value) {
    *optimal_value = x_max_value;
    *optimal_x = x_max;
  }

  // If the polynomial is linear or constant, we are done.
  if (polynomial.rows() <= 2) {
    return;
  }

  const Vector derivative = DifferentiatePolynomial(polynomial);
  Vector roots_real;
  if (!FindPolynomialRoots(derivative, &roots_real, nullptr)) {
    LOG(WARNING) << "Unable to find the critical points of "
                 << "the interpolating polynomial.";
    return;
  }

  // This is a bit of an overkill, as some of the roots may actually
  // have a complex part, but its simpler to just check these values.
  for (int i = 0; i < roots_real.rows(); ++i) {
    const double root = roots_real(i);
    if ((root < x_min) || (root > x_max)) {
      continue;
    }

    const double value = EvaluatePolynomial(polynomial, root);
    if (value < *optimal_value) {
      *optimal_value = value;
      *optimal_x = root;
    }
  }
}

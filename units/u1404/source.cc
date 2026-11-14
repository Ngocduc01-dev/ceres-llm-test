// u1404 – ceres::internal::MinimizeInterpolatingPolynomial
// Trích từ internal/ceres/polynomial.cc, dòng 369–387 (chỉ để xem, không compile)

void MinimizeInterpolatingPolynomial(const std::vector<FunctionSample>& samples,
                                     double x_min,
                                     double x_max,
                                     double* optimal_x,
                                     double* optimal_value) {
  const Vector polynomial = FindInterpolatingPolynomial(samples);
  MinimizePolynomial(polynomial, x_min, x_max, optimal_x, optimal_value);
  for (const auto& sample : samples) {
    if ((sample.x < x_min) || (sample.x > x_max)) {
      continue;
    }

    const double value = EvaluatePolynomial(polynomial, sample.x);
    if (value < *optimal_value) {
      *optimal_x = sample.x;
      *optimal_value = value;
    }
  }
}

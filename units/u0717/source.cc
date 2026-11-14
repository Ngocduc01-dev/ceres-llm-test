// u0717 – ceres::internal::EvaluatePolynomial
// Trích từ internal/ceres/polynomial.h, dòng 53–59 (chỉ để xem, không compile)

inline double EvaluatePolynomial(const Vector& polynomial, double x) {
  double v = 0.0;
  for (int i = 0; i < polynomial.size(); ++i) {
    v = v * x + polynomial(i);
  }
  return v;
}

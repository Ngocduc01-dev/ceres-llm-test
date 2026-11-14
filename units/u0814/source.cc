// u0814 – ceres::internal::(anonymous)::FindQuadraticPolynomialRoots
// Trích từ internal/ceres/polynomial.cc, dòng 138–179 (chỉ để xem, không compile)

void FindQuadraticPolynomialRoots(const Vector& polynomial,
                                  Vector* real,
                                  Vector* imaginary) {
  CHECK_EQ(polynomial.size(), 3);
  const double a = polynomial(0);
  const double b = polynomial(1);
  const double c = polynomial(2);
  const double D = b * b - 4 * a * c;
  const double sqrt_D = sqrt(fabs(D));
  if (real != nullptr) {
    real->setZero(2);
  }
  if (imaginary != nullptr) {
    imaginary->setZero(2);
  }

  // Real roots.
  if (D >= 0) {
    if (real != nullptr) {
      // Stable quadratic roots according to BKP Horn.
      // http://people.csail.mit.edu/bkph/articles/Quadratics.pdf
      if (b >= 0) {
        (*real)(0) = (-b - sqrt_D) / (2.0 * a);
        (*real)(1) = (2.0 * c) / (-b - sqrt_D);
      } else {
        (*real)(0) = (2.0 * c) / (-b + sqrt_D);
        (*real)(1) = (-b + sqrt_D) / (2.0 * a);
      }
    }
    return;
  }

  // Use the normal quadratic formula for the complex case.
  if (real != nullptr) {
    (*real)(0) = -b / (2.0 * a);
    (*real)(1) = -b / (2.0 * a);
  }
  if (imaginary != nullptr) {
    (*imaginary)(0) = sqrt_D / (2.0 * a);
    (*imaginary)(1) = -sqrt_D / (2.0 * a);
  }
}

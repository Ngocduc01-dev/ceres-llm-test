// u0807 – ceres::internal::(anonymous)::FindLinearPolynomialRoots
// Trích từ internal/ceres/polynomial.cc, dòng 124–136 (chỉ để xem, không compile)

void FindLinearPolynomialRoots(const Vector& polynomial,
                               Vector* real,
                               Vector* imaginary) {
  CHECK_EQ(polynomial.size(), 2);
  if (real != nullptr) {
    real->resize(1);
    (*real)(0) = -polynomial(1) / polynomial(0);
  }

  if (imaginary != nullptr) {
    imaginary->setZero(1);
  }
}

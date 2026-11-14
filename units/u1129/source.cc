// u1129 – ceres::internal::FindPolynomialRoots
// Trích từ internal/ceres/polynomial.cc, dòng 182–251 (chỉ để xem, không compile)

bool FindPolynomialRoots(const Vector& polynomial_in,
                         Vector* real,
                         Vector* imaginary) {
  if (polynomial_in.size() == 0) {
    LOG(ERROR) << "Invalid polynomial of size 0 passed to FindPolynomialRoots";
    return false;
  }

  Vector polynomial = RemoveLeadingZeros(polynomial_in);
  const int degree = polynomial.size() - 1;

  VLOG(3) << "Input polynomial: " << polynomial_in.transpose();
  if (polynomial.size() != polynomial_in.size()) {
    VLOG(3) << "Trimmed polynomial: " << polynomial.transpose();
  }

  // Is the polynomial constant?
  if (degree == 0) {
    LOG(WARNING) << "Trying to extract roots from a constant "
                 << "polynomial in FindPolynomialRoots";
    // We return true with no roots, not false, as if the polynomial is constant
    // it is correct that there are no roots. It is not the case that they were
    // there, but that we have failed to extract them.
    return true;
  }

  // Linear
  if (degree == 1) {
    FindLinearPolynomialRoots(polynomial, real, imaginary);
    return true;
  }

  // Quadratic
  if (degree == 2) {
    FindQuadraticPolynomialRoots(polynomial, real, imaginary);
    return true;
  }

  // The degree is now known to be at least 3. For cubic or higher
  // roots we use the method of companion matrices.

  // Divide by leading term
  const double leading_term = polynomial(0);
  polynomial /= leading_term;

  // Build and balance the companion matrix to the polynomial.
  Matrix companion_matrix(degree, degree);
  BuildCompanionMatrix(polynomial, &companion_matrix);
  BalanceCompanionMatrix(&companion_matrix);

  // Find its (complex) eigenvalues.
  Eigen::EigenSolver<Matrix> solver(companion_matrix, false);
  if (solver.info() != Eigen::Success) {
    LOG(ERROR) << "Failed to extract eigenvalues from companion matrix.";
    return false;
  }

  // Output roots
  if (real != nullptr) {
    *real = solver.eigenvalues().real();
  } else {
    LOG(WARNING) << "nullptr pointer passed as real argument to "
                 << "FindPolynomialRoots. Real parts of the roots will not "
                 << "be returned.";
  }
  if (imaginary != nullptr) {
    *imaginary = solver.eigenvalues().imag();
  }
  return true;
}

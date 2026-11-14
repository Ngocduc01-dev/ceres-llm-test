// u0800 – ceres::internal::(anonymous)::BuildCompanionMatrix
// Trích từ internal/ceres/polynomial.cc, dòng 102–113 (chỉ để xem, không compile)

void BuildCompanionMatrix(const Vector& polynomial,
                          Matrix* companion_matrix_ptr) {
  CHECK(companion_matrix_ptr != nullptr);
  Matrix& companion_matrix = *companion_matrix_ptr;

  const int degree = polynomial.size() - 1;

  companion_matrix.resize(degree, degree);
  companion_matrix.setZero();
  companion_matrix.diagonal(-1).setOnes();
  companion_matrix.col(degree - 1) = -polynomial.reverse().head(degree);
}

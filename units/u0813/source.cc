// u0813 – ceres::internal::(anonymous)::BalanceCompanionMatrix
// Trích từ internal/ceres/polynomial.cc, dòng 51–100 (chỉ để xem, không compile)

void BalanceCompanionMatrix(Matrix* companion_matrix_ptr) {
  CHECK(companion_matrix_ptr != nullptr);
  Matrix& companion_matrix = *companion_matrix_ptr;
  Matrix companion_matrix_offdiagonal = companion_matrix;
  companion_matrix_offdiagonal.diagonal().setZero();

  const int degree = companion_matrix.rows();

  // gamma <= 1 controls how much a change in the scaling has to
  // lower the 1-norm of the companion matrix to be accepted.
  //
  // gamma = 1 seems to lead to cycles (numerical issues?), so
  // we set it slightly lower.
  const double gamma = 0.9;

  // Greedily scale row/column pairs until there is no change.
  bool scaling_has_changed;
  do {
    scaling_has_changed = false;

    for (int i = 0; i < degree; ++i) {
      const double row_norm = companion_matrix_offdiagonal.row(i).lpNorm<1>();
      const double col_norm = companion_matrix_offdiagonal.col(i).lpNorm<1>();

      // Decompose row_norm/col_norm into mantissa * 2^exponent,
      // where 0.5 <= mantissa < 1. Discard mantissa (return value
      // of frexp), as only the exponent is needed.
      int exponent = 0;
      std::frexp(row_norm / col_norm, &exponent);
      exponent /= 2;

      if (exponent != 0) {
        const double scaled_col_norm = std::ldexp(col_norm, exponent);
        const double scaled_row_norm = std::ldexp(row_norm, -exponent);
        if (scaled_col_norm + scaled_row_norm < gamma * (col_norm + row_norm)) {
          // Accept the new scaling. (Multiplication by powers of 2 should not
          // introduce rounding errors (ignoring non-normalized numbers and
          // over- or underflow))
          scaling_has_changed = true;
          companion_matrix_offdiagonal.row(i) *= std::ldexp(1.0, -exponent);
          companion_matrix_offdiagonal.col(i) *= std::ldexp(1.0, exponent);
        }
      }
    }
  } while (scaling_has_changed);

  companion_matrix_offdiagonal.diagonal() = companion_matrix.diagonal();
  companion_matrix = companion_matrix_offdiagonal;
  VLOG(3) << "Balanced companion matrix is\n" << companion_matrix;
}

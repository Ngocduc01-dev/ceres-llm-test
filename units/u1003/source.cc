// u1003 – ceres::internal::ImplicitSchurComplement::BackSubstitute
// Trích từ internal/ceres/implicit_schur_complement.cc, dòng 208–243 (chỉ để xem, không compile)

void ImplicitSchurComplement::BackSubstitute(const double* x, double* y) {
  const int num_cols_e = A_->num_cols_e();
  const int num_cols_f = A_->num_cols_f();
  const int num_cols = A_->num_cols();
  const int num_rows = A_->num_rows();

  // y1 = F x
  ParallelSetZero(options_.context, options_.num_threads, tmp_rows_);
  A_->RightMultiplyAndAccumulateF(x, tmp_rows_.data());

  // y2 = b - y1
  ParallelAssign(options_.context,
                 options_.num_threads,
                 tmp_rows_,
                 ConstVectorRef(b_, num_rows) - tmp_rows_);

  // y3 = E' y2
  ParallelSetZero(options_.context, options_.num_threads, tmp_e_cols_);
  A_->LeftMultiplyAndAccumulateE(tmp_rows_.data(), tmp_e_cols_.data());

  // y = (E'E)^-1 y3
  ParallelSetZero(options_.context, options_.num_threads, y, num_cols);
  block_diagonal_EtE_inverse_->RightMultiplyAndAccumulate(
      tmp_e_cols_.data(), y, options_.context, options_.num_threads);

  // The full solution vector y has two blocks. The first block of
  // variables corresponds to the eliminated variables, which we just
  // computed via back substitution. The second block of variables
  // corresponds to the Schur complement system, so we just copy those
  // values from the solution to the Schur complement.
  VectorRef y_cols_f(y + num_cols_e, num_cols_f);
  ParallelAssign(options_.context,
                 options_.num_threads,
                 y_cols_f,
                 ConstVectorRef(x, num_cols_f));
}

// u1032 – ceres::internal::ImplicitSchurComplement::RightMultiplyAndAccumulate
// Trích từ internal/ceres/implicit_schur_complement.cc, dòng 106–144 (chỉ để xem, không compile)

void ImplicitSchurComplement::RightMultiplyAndAccumulate(const double* x,
                                                         double* y) const {
  // y1 = F x
  ParallelSetZero(options_.context, options_.num_threads, tmp_rows_);
  A_->RightMultiplyAndAccumulateF(x, tmp_rows_.data());

  // y2 = E' y1
  ParallelSetZero(options_.context, options_.num_threads, tmp_e_cols_);
  A_->LeftMultiplyAndAccumulateE(tmp_rows_.data(), tmp_e_cols_.data());

  // y3 = -(E'E)^-1 y2
  ParallelSetZero(options_.context, options_.num_threads, tmp_e_cols_2_);
  block_diagonal_EtE_inverse_->RightMultiplyAndAccumulate(tmp_e_cols_.data(),
                                                          tmp_e_cols_2_.data(),
                                                          options_.context,
                                                          options_.num_threads);

  ParallelAssign(
      options_.context, options_.num_threads, tmp_e_cols_2_, -tmp_e_cols_2_);

  // y1 = y1 + E y3
  A_->RightMultiplyAndAccumulateE(tmp_e_cols_2_.data(), tmp_rows_.data());

  // y5 = D * x
  if (D_ != nullptr) {
    ConstVectorRef Dref(D_ + A_->num_cols_e(), num_cols());
    VectorRef y_cols(y, num_cols());
    ParallelAssign(
        options_.context,
        options_.num_threads,
        y_cols,
        (Dref.array().square() * ConstVectorRef(x, num_cols()).array()));
  } else {
    ParallelSetZero(options_.context, options_.num_threads, y, num_cols());
  }

  // y = y5 + F' y1
  A_->LeftMultiplyAndAccumulateF(tmp_rows_.data(), y);
}

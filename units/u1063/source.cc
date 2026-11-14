// u1063 – ceres::internal::ImplicitSchurComplement::UpdateRhs
// Trích từ internal/ceres/implicit_schur_complement.cc, dòng 251–276 (chỉ để xem, không compile)

void ImplicitSchurComplement::UpdateRhs() {
  // y1 = E'b
  ParallelSetZero(options_.context, options_.num_threads, tmp_e_cols_);
  A_->LeftMultiplyAndAccumulateE(b_, tmp_e_cols_.data());

  // y2 = (E'E)^-1 y1
  ParallelSetZero(options_.context, options_.num_threads, tmp_e_cols_2_);
  block_diagonal_EtE_inverse_->RightMultiplyAndAccumulate(tmp_e_cols_.data(),
                                                          tmp_e_cols_2_.data(),
                                                          options_.context,
                                                          options_.num_threads);

  // y3 = E y2
  ParallelSetZero(options_.context, options_.num_threads, tmp_rows_);
  A_->RightMultiplyAndAccumulateE(tmp_e_cols_2_.data(), tmp_rows_.data());

  // y3 = b - y3
  ParallelAssign(options_.context,
                 options_.num_threads,
                 tmp_rows_,
                 ConstVectorRef(b_, A_->num_rows()) - tmp_rows_);

  // rhs = F' y3
  ParallelSetZero(options_.context, options_.num_threads, rhs_);
  A_->LeftMultiplyAndAccumulateF(tmp_rows_.data(), rhs_.data());
}

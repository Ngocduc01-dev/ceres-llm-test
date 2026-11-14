// u1033 – ceres::internal::ImplicitSchurComplement::InversePowerSeriesOperatorRightMultiplyAccumulate
// Trích từ internal/ceres/implicit_schur_complement.cc, dòng 146–174 (chỉ để xem, không compile)

void ImplicitSchurComplement::InversePowerSeriesOperatorRightMultiplyAccumulate(
    const double* x, double* y) const {
  CHECK(compute_ftf_inverse_);
  // y1 = F x
  ParallelSetZero(options_.context, options_.num_threads, tmp_rows_);
  A_->RightMultiplyAndAccumulateF(x, tmp_rows_.data());

  // y2 = E' y1
  ParallelSetZero(options_.context, options_.num_threads, tmp_e_cols_);
  A_->LeftMultiplyAndAccumulateE(tmp_rows_.data(), tmp_e_cols_.data());

  // y3 = (E'E)^-1 y2
  ParallelSetZero(options_.context, options_.num_threads, tmp_e_cols_2_);
  block_diagonal_EtE_inverse_->RightMultiplyAndAccumulate(tmp_e_cols_.data(),
                                                          tmp_e_cols_2_.data(),
                                                          options_.context,
                                                          options_.num_threads);
  // y1 = E y3
  ParallelSetZero(options_.context, options_.num_threads, tmp_rows_);
  A_->RightMultiplyAndAccumulateE(tmp_e_cols_2_.data(), tmp_rows_.data());

  // y4 = F' y1
  ParallelSetZero(options_.context, options_.num_threads, tmp_f_cols_);
  A_->LeftMultiplyAndAccumulateF(tmp_rows_.data(), tmp_f_cols_.data());

  // y += (F'F)^-1 y4
  block_diagonal_FtF_inverse_->RightMultiplyAndAccumulate(
      tmp_f_cols_.data(), y, options_.context, options_.num_threads);
}

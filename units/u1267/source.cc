// u1267 – ceres::internal::PowerSeriesExpansionPreconditioner::RightMultiplyAndAccumulate
// Trích từ internal/ceres/power_series_expansion_preconditioner.cc, dòng 57–82 (chỉ để xem, không compile)

void PowerSeriesExpansionPreconditioner::RightMultiplyAndAccumulate(
    const double* x, double* y) const {
  VectorRef yref(y, num_rows());
  Vector series_term(num_rows());
  Vector previous_series_term(num_rows());
  ParallelSetZero(options_.context, options_.num_threads, yref);
  isc_->block_diagonal_FtF_inverse()->RightMultiplyAndAccumulate(
      x, y, options_.context, options_.num_threads);
  ParallelAssign(
      options_.context, options_.num_threads, previous_series_term, yref);

  const double norm_threshold =
      spse_tolerance_ * Norm(yref, options_.context, options_.num_threads);

  for (int i = 1;; i++) {
    ParallelSetZero(options_.context, options_.num_threads, series_term);
    isc_->InversePowerSeriesOperatorRightMultiplyAccumulate(
        previous_series_term.data(), series_term.data());
    ParallelAssign(
        options_.context, options_.num_threads, yref, yref + series_term);
    if (i >= max_num_spse_iterations_ || series_term.norm() < norm_threshold) {
      break;
    }
    std::swap(previous_series_term, series_term);
  }
}

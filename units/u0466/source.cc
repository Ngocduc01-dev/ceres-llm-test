// u0466 – ceres::internal::Corrector::CorrectResiduals
// Trích từ internal/ceres/corrector.cc, dòng 112–116 (chỉ để xem, không compile)

void Corrector::CorrectResiduals(const int num_rows, double* residuals) {
  DCHECK(residuals != nullptr);
  // Equation 11 in BAMS.
  VectorRef(residuals, num_rows) *= residual_scaling_;
}

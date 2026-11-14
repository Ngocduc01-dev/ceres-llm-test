// u0552 – ceres::internal::Corrector::CorrectJacobian
// Trích từ internal/ceres/corrector.cc, dòng 118–155 (chỉ để xem, không compile)

void Corrector::CorrectJacobian(const int num_rows,
                                const int num_cols,
                                double* residuals,
                                double* jacobian) {
  DCHECK(residuals != nullptr);
  DCHECK(jacobian != nullptr);

  // The common case (rho[2] <= 0).
  if (alpha_sq_norm_ == 0.0) {
    VectorRef(jacobian, num_rows * num_cols) *= sqrt_rho1_;
    return;
  }

  // Equation 11 in BAMS.
  //
  //  J = sqrt(rho) * (J - alpha^2 r * r' J)
  //
  // In days gone by this loop used to be a single Eigen expression of
  // the form
  //
  //  J = sqrt_rho1_ * (J - alpha_sq_norm_ * r* (r.transpose() * J));
  //
  // Which turns out to about 17x slower on bal problems. The reason
  // is that Eigen is unable to figure out that this expression can be
  // evaluated columnwise and ends up creating a temporary.
  for (int c = 0; c < num_cols; ++c) {
    double r_transpose_j = 0.0;
    for (int r = 0; r < num_rows; ++r) {
      r_transpose_j += jacobian[r * num_cols + c] * residuals[r];
    }

    for (int r = 0; r < num_rows; ++r) {
      jacobian[r * num_cols + c] =
          sqrt_rho1_ * (jacobian[r * num_cols + c] -
                        alpha_sq_norm_ * residuals[r] * r_transpose_j);
    }
  }
}

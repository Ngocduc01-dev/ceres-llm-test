// u0550 – ceres::internal::LowRankInverseHessian::RightMultiplyAndAccumulate
// Trích từ internal/ceres/low_rank_inverse_hessian.cc, dòng 117–177 (chỉ để xem, không compile)

void LowRankInverseHessian::RightMultiplyAndAccumulate(const double* x_ptr,
                                                       double* y_ptr) const {
  ConstVectorRef gradient(x_ptr, num_parameters_);
  VectorRef search_direction(y_ptr, num_parameters_);

  search_direction = gradient;

  const int num_corrections = indices_.size();
  Vector alpha(num_corrections);

  for (auto it = indices_.rbegin(); it != indices_.rend(); ++it) {
    const double alpha_i = delta_x_history_.col(*it).dot(search_direction) /
                           delta_x_dot_delta_gradient_(*it);
    search_direction -= alpha_i * delta_gradient_history_.col(*it);
    alpha(*it) = alpha_i;
  }

  if (use_approximate_eigenvalue_scaling_) {
    // Rescale the initial inverse Hessian approximation (H_0) to be iteratively
    // updated so that it is of similar 'size' to the true inverse Hessian along
    // the most recent search direction.  As shown in [1]:
    //
    //   \gamma_k = (delta_gradient_{k-1}' * delta_x_{k-1}) /
    //              (delta_gradient_{k-1}' * delta_gradient_{k-1})
    //
    // Satisfies:
    //
    //   (1 / \lambda_m) <= \gamma_k <= (1 / \lambda_1)
    //
    // Where \lambda_1 & \lambda_m are the smallest and largest eigenvalues of
    // the true Hessian (not the inverse) along the most recent search direction
    // respectively.  Thus \gamma is an approximate eigenvalue of the true
    // inverse Hessian, and choosing: H_0 = I * \gamma will yield a starting
    // point that has a similar scale to the true inverse Hessian.  This
    // technique is widely reported to often improve convergence, however this
    // is not universally true, particularly if there are errors in the initial
    // jacobians, or if there are significant differences in the sensitivity
    // of the problem to the parameters (i.e. the range of the magnitudes of
    // the components of the gradient is large).
    //
    // The original origin of this rescaling trick is somewhat unclear, the
    // earliest reference appears to be Oren [1], however it is widely discussed
    // without specific attribution in various texts including [2] (p143/178).
    //
    // [1] Oren S.S., Self-scaling variable metric (SSVM) algorithms Part II:
    //     Implementation and experiments, Management Science,
    //     20(5), 863-874, 1974.
    // [2] Nocedal J., Wright S., Numerical Optimization, Springer, 1999.
    search_direction *= approximate_eigenvalue_scale_;

    VLOG(4) << "Applying approximate_eigenvalue_scale: "
            << approximate_eigenvalue_scale_ << " to initial inverse Hessian "
            << "approximation.";
  }

  for (const int i : indices_) {
    const double beta = delta_gradient_history_.col(i).dot(search_direction) /
                        delta_x_dot_delta_gradient_(i);
    search_direction += delta_x_history_.col(i) * (alpha(i) - beta);
  }
}

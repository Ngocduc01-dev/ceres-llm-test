// u0538 – ceres::internal::Corrector::Corrector
// Trích từ internal/ceres/corrector.cc, dòng 41–110 (chỉ để xem, không compile)

Corrector::Corrector(const double sq_norm, const double rho[3]) {
  CHECK_GE(sq_norm, 0.0);
  sqrt_rho1_ = sqrt(rho[1]);

  // If sq_norm = 0.0, the correction becomes trivial, the residual
  // and the jacobian are scaled by the square root of the derivative
  // of rho. Handling this case explicitly avoids the divide by zero
  // error that would occur below.
  //
  // The case where rho'' < 0 also gets special handling. Technically
  // it shouldn't, and the computation of the scaling should proceed
  // as below, however we found in experiments that applying the
  // curvature correction when rho'' < 0, which is the case when we
  // are in the outlier region slows down the convergence of the
  // algorithm significantly.
  //
  // Thus, we have divided the action of the robustifier into two
  // parts. In the inliner region, we do the full second order
  // correction which re-wights the gradient of the function by the
  // square root of the derivative of rho, and the Gauss-Newton
  // Hessian gets both the scaling and the rank-1 curvature
  // correction. Normally, alpha is upper bounded by one, but with this
  // change, alpha is bounded above by zero.
  //
  // Empirically we have observed that the full Triggs correction and
  // the clamped correction both start out as very good approximations
  // to the loss function when we are in the convex part of the
  // function, but as the function starts transitioning from convex to
  // concave, the Triggs approximation diverges more and more and
  // ultimately becomes linear. The clamped Triggs model however
  // remains quadratic.
  //
  // The reason why the Triggs approximation becomes so poor is
  // because the curvature correction that it applies to the gauss
  // newton hessian goes from being a full rank correction to a rank
  // deficient correction making the inversion of the Hessian fraught
  // with all sorts of misery and suffering.
  //
  // The clamped correction retains its quadratic nature and inverting it
  // is always well formed.
  if ((sq_norm == 0.0) || (rho[2] <= 0.0)) {
    residual_scaling_ = sqrt_rho1_;
    alpha_sq_norm_ = 0.0;
    return;
  }

  // We now require that the first derivative of the loss function be
  // positive only if the second derivative is positive. This is
  // because when the second derivative is non-positive, we do not use
  // the second order correction suggested by BAMS and instead use a
  // simpler first order strategy which does not use a division by the
  // gradient of the loss function.
  CHECK_GT(rho[1], 0.0);

  // Calculate the smaller of the two solutions to the equation
  //
  // 0.5 *  alpha^2 - alpha - rho'' / rho' *  z'z = 0.
  //
  // Start by calculating the discriminant D.
  const double D = 1.0 + 2.0 * sq_norm * rho[2] / rho[1];

  // Since both rho[1] and rho[2] are guaranteed to be positive at
  // this point, we know that D > 1.0.

  const double alpha = 1.0 - sqrt(D);

  // Calculate the constants needed by the correction routines.
  residual_scaling_ = sqrt_rho1_ / (1 - alpha);
  alpha_sq_norm_ = alpha / sq_norm;
}

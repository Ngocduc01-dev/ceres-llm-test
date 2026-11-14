// u1234 – ceres::internal::TrustRegionMinimizer::EvaluateGradientAndJacobian
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 244–302 (chỉ để xem, không compile)

bool TrustRegionMinimizer::EvaluateGradientAndJacobian(
    bool new_evaluation_point) {
  Evaluator::EvaluateOptions evaluate_options;
  evaluate_options.new_evaluation_point = new_evaluation_point;
  if (!evaluator_->Evaluate(evaluate_options,
                            x_.data(),
                            &x_cost_,
                            residuals_.data(),
                            gradient_.data(),
                            jacobian_)) {
    solver_summary_->message = "Residual and Jacobian evaluation failed.";
    solver_summary_->termination_type = FAILURE;
    return false;
  }

  iteration_summary_.cost = x_cost_ + solver_summary_->fixed_cost;

  if (options_.jacobi_scaling) {
    if (iteration_summary_.iteration == 0) {
      // Compute a scaling vector that is used to improve the
      // conditioning of the Jacobian.
      //
      // jacobian_scaling_ = diag(J'J)^{-1}
      jacobian_->SquaredColumnNorm(jacobian_scaling_.data());
      for (int i = 0; i < jacobian_->num_cols(); ++i) {
        // Add one to the denominator to prevent division by zero.
        jacobian_scaling_[i] = 1.0 / (1.0 + sqrt(jacobian_scaling_[i]));
      }
    }

    // jacobian = jacobian * diag(J'J) ^{-1}
    jacobian_->ScaleColumns(
        jacobian_scaling_.data(), options_.context, options_.num_threads);
  }

  // The gradient exists in the local tangent space. To account for
  // the bounds constraints correctly, instead of just computing the
  // norm of the gradient vector, we compute
  //
  // |Plus(x, -gradient) - x|
  //
  // Where the Plus operator lifts the negative gradient to the
  // ambient space, adds it to x and projects it on the hypercube
  // defined by the bounds.
  negative_gradient_ = -gradient_;
  if (!evaluator_->Plus(x_.data(),
                        negative_gradient_.data(),
                        projected_gradient_step_.data())) {
    solver_summary_->message =
        "projected_gradient_step = Plus(x, -gradient) failed.";
    solver_summary_->termination_type = FAILURE;
    return false;
  }

  iteration_summary_.gradient_max_norm =
      (x_ - projected_gradient_step_).lpNorm<Eigen::Infinity>();
  iteration_summary_.gradient_norm = (x_ - projected_gradient_step_).norm();
  return true;
}

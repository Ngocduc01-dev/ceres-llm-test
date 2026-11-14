// u1128 – ceres::TinySolver::Solve
// Trích từ include/ceres/tiny_solver.h, dòng 220–330 (chỉ để xem, không compile)

  const Summary& Solve(const Function& function, Parameters* x_and_min) {
    Initialize<NUM_RESIDUALS, NUM_PARAMETERS>(function);
    assert(x_and_min);
    Parameters& x = *x_and_min;
    summary = Summary();
    summary.iterations = 0;

    // TODO(sameeragarwal): Deal with failure here.
    Update(function, x);
    summary.initial_cost = cost_;
    summary.final_cost = cost_;

    if (summary.gradient_max_norm < options.gradient_tolerance) {
      summary.status = GRADIENT_TOO_SMALL;
      return summary;
    }

    if (cost_ < options.cost_threshold) {
      summary.status = COST_TOO_SMALL;
      return summary;
    }

    Scalar u = 1.0 / options.initial_trust_region_radius;
    Scalar v = 2;

    for (summary.iterations = 1;
         summary.iterations < options.max_num_iterations;
         summary.iterations++) {
      jtj_regularized_ = jtj_;
      const Scalar min_diagonal = 1e-6;
      const Scalar max_diagonal = 1e32;
      for (int i = 0; i < dx_.rows(); ++i) {
        jtj_regularized_(i, i) +=
            u * (std::min)((std::max)(jtj_(i, i), min_diagonal), max_diagonal);
      }

      // TODO(sameeragarwal): Check for failure and deal with it.
      linear_solver_.compute(jtj_regularized_);
      lm_step_ = linear_solver_.solve(g_);
      dx_ = jacobi_scaling_.asDiagonal() * lm_step_;

      // Adding parameter_tolerance to x.norm() ensures that this
      // works if x is near zero.
      const Scalar parameter_tolerance =
          options.parameter_tolerance *
          (x.norm() + options.parameter_tolerance);
      if (dx_.norm() < parameter_tolerance) {
        summary.status = RELATIVE_STEP_SIZE_TOO_SMALL;
        break;
      }
      x_new_ = x + dx_;

      // TODO(keir): Add proper handling of errors from user eval of cost
      // functions.
      function(&x_new_[0], &f_x_new_[0], nullptr);

      const Scalar cost_change = (2 * cost_ - f_x_new_.squaredNorm());
      // TODO(sameeragarwal): Better more numerically stable evaluation.
      const Scalar model_cost_change = lm_step_.dot(2 * g_ - jtj_ * lm_step_);

      // rho is the ratio of the actual reduction in error to the reduction
      // in error that would be obtained if the problem was linear. See [1]
      // for details.
      Scalar rho(cost_change / model_cost_change);
      if (rho > 0) {
        // Accept the Levenberg-Marquardt step because the linear
        // model fits well.
        x = x_new_;

        if (std::abs(cost_change) < options.function_tolerance) {
          cost_ = f_x_new_.squaredNorm() / 2;
          summary.status = COST_CHANGE_TOO_SMALL;
          break;
        }

        // TODO(sameeragarwal): Deal with failure.
        Update(function, x);
        if (summary.gradient_max_norm < options.gradient_tolerance) {
          summary.status = GRADIENT_TOO_SMALL;
          break;
        }

        if (cost_ < options.cost_threshold) {
          summary.status = COST_TOO_SMALL;
          break;
        }

        Scalar tmp = Scalar(2 * rho - 1);
        u = u * (std::max)(Scalar(1 / 3.), Scalar(1) - tmp * tmp * tmp);
        v = 2;

      } else {
        // Reject the update because either the normal equations failed to solve
        // or the local linear model was not good (rho < 0).

        // Additionally if the cost change is too small, then terminate.
        if (std::abs(cost_change) < options.function_tolerance) {
          // Terminate
          summary.status = COST_CHANGE_TOO_SMALL;
          break;
        }

        // Reduce the size of the trust region.
        u *= v;
        v *= 2;
      }
    }

    summary.final_cost = cost_;
    return summary;
  }

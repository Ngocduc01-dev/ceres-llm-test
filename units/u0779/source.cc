// u0779 – ceres::internal::BFGS::NextDirection
// Trích từ internal/ceres/line_search_direction.cc, dòng 164–329 (chỉ để xem, không compile)

  bool NextDirection(const LineSearchMinimizer::State& previous,
                     const LineSearchMinimizer::State& current,
                     Vector* search_direction) override {
    CHECK(is_positive_definite_)
        << "Ceres bug: NextDirection() called on BFGS after inverse Hessian "
        << "approximation has become indefinite, please contact the "
        << "developers!";

    const Vector delta_x = previous.search_direction * previous.step_size;
    const Vector delta_gradient = current.gradient - previous.gradient;
    const double delta_x_dot_delta_gradient = delta_x.dot(delta_gradient);

    // The (L)BFGS algorithm explicitly requires that the secant equation:
    //
    //   B_{k+1} * s_k = y_k
    //
    // Is satisfied at each iteration, where B_{k+1} is the approximated
    // Hessian at the k+1-th iteration, s_k = (x_{k+1} - x_{k}) and
    // y_k = (grad_{k+1} - grad_{k}). As the approximated Hessian must be
    // positive definite, this is equivalent to the condition:
    //
    //   s_k^T * y_k > 0     [s_k^T * B_{k+1} * s_k = s_k^T * y_k > 0]
    //
    // This condition would always be satisfied if the function was strictly
    // convex, alternatively, it is always satisfied provided that a Wolfe line
    // search is used (even if the function is not strictly convex).  See [1]
    // (p138) for a proof.
    //
    // Although Ceres will always use a Wolfe line search when using (L)BFGS,
    // practical implementation considerations mean that the line search
    // may return a point that satisfies only the Armijo condition, and thus
    // could violate the Secant equation.  As such, we will only use a step
    // to update the Hessian approximation if:
    //
    //   s_k^T * y_k > tolerance
    //
    // It is important that tolerance is very small (and >=0), as otherwise we
    // might skip the update too often and fail to capture important curvature
    // information in the Hessian.  For example going from 1e-10 -> 1e-14
    // improves the NIST benchmark score from 43/54 to 53/54.
    //
    // [1] Nocedal J, Wright S, Numerical Optimization, 2nd Ed. Springer, 1999.
    //
    // TODO(alexs.mac): Consider using Damped BFGS update instead of
    // skipping update.
    const double kBFGSSecantConditionHessianUpdateTolerance = 1e-14;
    if (delta_x_dot_delta_gradient <=
        kBFGSSecantConditionHessianUpdateTolerance) {
      VLOG(2) << "Skipping BFGS Update, delta_x_dot_delta_gradient too "
              << "small: " << delta_x_dot_delta_gradient
              << ", tolerance: " << kBFGSSecantConditionHessianUpdateTolerance
              << " (Secant condition).";
    } else {
      // Update dense inverse Hessian approximation.

      if (!initialized_ && use_approximate_eigenvalue_scaling_) {
        // Rescale the initial inverse Hessian approximation (H_0) to be
        // iteratively updated so that it is of similar 'size' to the true
        // inverse Hessian at the start point.  As shown in [1]:
        //
        //   \gamma = (delta_gradient_{0}' * delta_x_{0}) /
        //            (delta_gradient_{0}' * delta_gradient_{0})
        //
        // Satisfies:
        //
        //   (1 / \lambda_m) <= \gamma <= (1 / \lambda_1)
        //
        // Where \lambda_1 & \lambda_m are the smallest and largest eigenvalues
        // of the true initial Hessian (not the inverse) respectively. Thus,
        // \gamma is an approximate eigenvalue of the true inverse Hessian, and
        // choosing: H_0 = I * \gamma will yield a starting point that has a
        // similar scale to the true inverse Hessian.  This technique is widely
        // reported to often improve convergence, however this is not
        // universally true, particularly if there are errors in the initial
        // gradients, or if there are significant differences in the sensitivity
        // of the problem to the parameters (i.e. the range of the magnitudes of
        // the components of the gradient is large).
        //
        // The original origin of this rescaling trick is somewhat unclear, the
        // earliest reference appears to be Oren [1], however it is widely
        // discussed without specific attribution in various texts including
        // [2] (p143).
        //
        // [1] Oren S.S., Self-scaling variable metric (SSVM) algorithms
        //     Part II: Implementation and experiments, Management Science,
        //     20(5), 863-874, 1974.
        // [2] Nocedal J., Wright S., Numerical Optimization, Springer, 1999.
        const double approximate_eigenvalue_scale =
            delta_x_dot_delta_gradient / delta_gradient.dot(delta_gradient);
        inverse_hessian_ *= approximate_eigenvalue_scale;

        VLOG(4) << "Applying approximate_eigenvalue_scale: "
                << approximate_eigenvalue_scale << " to initial inverse "
                << "Hessian approximation.";
      }
      initialized_ = true;

      // Efficient O(num_parameters^2) BFGS update [2].
      //
      // Starting from dense BFGS update detailed in Nocedal [2] p140/177 and
      // using: y_k = delta_gradient, s_k = delta_x:
      //
      //   \rho_k = 1.0 / (s_k' * y_k)
      //   V_k = I - \rho_k * y_k * s_k'
      //   H_k = (V_k' * H_{k-1} * V_k) + (\rho_k * s_k * s_k')
      //
      // This update involves matrix, matrix products which naively O(N^3),
      // however we can exploit our knowledge that H_k is positive definite
      // and thus by defn. symmetric to reduce the cost of the update:
      //
      // Expanding the update above yields:
      //
      //   H_k = H_{k-1} +
      //         \rho_k * ( (1.0 + \rho_k * y_k' * H_k * y_k) * s_k * s_k' -
      //                    (s_k * y_k' * H_k + H_k * y_k * s_k') )
      //
      // Using: A = (s_k * y_k' * H_k), and the knowledge that H_k = H_k', the
      // last term simplifies to (A + A'). Note that although A is not symmetric
      // (A + A') is symmetric. For ease of construction we also define
      // B = (1 + \rho_k * y_k' * H_k * y_k) * s_k * s_k', which is by defn
      // symmetric due to construction from: s_k * s_k'.
      //
      // Now we can write the BFGS update as:
      //
      //   H_k = H_{k-1} + \rho_k * (B - (A + A'))

      // For efficiency, as H_k is by defn. symmetric, we will only maintain the
      // *lower* triangle of H_k (and all intermediary terms).

      const double rho_k = 1.0 / delta_x_dot_delta_gradient;

      // Calculate: A = s_k * y_k' * H_k
      Matrix A = delta_x * (delta_gradient.transpose() *
                            inverse_hessian_.selfadjointView<Eigen::Lower>());

      // Calculate scalar: (1 + \rho_k * y_k' * H_k * y_k)
      const double delta_x_times_delta_x_transpose_scale_factor =
          (1.0 +
           (rho_k * delta_gradient.transpose() *
            inverse_hessian_.selfadjointView<Eigen::Lower>() * delta_gradient));
      // Calculate: B = (1 + \rho_k * y_k' * H_k * y_k) * s_k * s_k'
      Matrix B = Matrix::Zero(num_parameters_, num_parameters_);
      B.selfadjointView<Eigen::Lower>().rankUpdate(
          delta_x, delta_x_times_delta_x_transpose_scale_factor);

      // Finally, update inverse Hessian approximation according to:
      // H_k = H_{k-1} + \rho_k * (B - (A + A')).  Note that (A + A') is
      // symmetric, even though A is not.
      inverse_hessian_.triangularView<Eigen::Lower>() +=
          rho_k * (B - A - A.transpose());
    }

    *search_direction = inverse_hessian_.selfadjointView<Eigen::Lower>() *
                        (-1.0 * current.gradient);

    if (search_direction->dot(current.gradient) >= 0.0) {
      LOG(WARNING) << "Numerical failure in BFGS update: inverse Hessian "
                   << "approximation is not positive definite, and thus "
                   << "initial gradient for search direction is positive: "
                   << search_direction->dot(current.gradient);
      is_positive_definite_ = false;
      return false;
    }

    return true;
  }

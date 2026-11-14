// u1127 – ceres::internal::NumericDiff::EvaluateRiddersJacobianColumn
// Trích từ include/ceres/internal/numeric_diff.h, dòng 245–383 (chỉ để xem, không compile)

  static bool EvaluateRiddersJacobianColumn(
      const CostFunctor* functor,
      int parameter_index,
      double delta,
      const NumericDiffOptions& options,
      int num_residuals,
      int parameter_block_size,
      const double* x_ptr,
      const double* residuals_at_eval_point,
      double** parameters,
      double* x_plus_delta_ptr,
      double* temp_residuals_ptr,
      double* residuals_ptr) {
    using Eigen::aligned_allocator;
    using Eigen::Map;
    using Eigen::Matrix;

    using ResidualVector = Matrix<double, kNumResiduals, 1>;
    using ResidualCandidateMatrix =
        Matrix<double, kNumResiduals, Eigen::Dynamic>;
    using ParameterVector = Matrix<double, kParameterBlockSize, 1>;

    Map<const ParameterVector> x(x_ptr, parameter_block_size);
    Map<ParameterVector> x_plus_delta(x_plus_delta_ptr, parameter_block_size);

    Map<ResidualVector> residuals(residuals_ptr, num_residuals);
    Map<ResidualVector> temp_residuals(temp_residuals_ptr, num_residuals);

    // In order for the algorithm to converge, the step size should be
    // initialized to a value that is large enough to produce a significant
    // change in the function.
    // As the derivative is estimated, the step size decreases.
    // By default, the step sizes are chosen so that the middle column
    // of the Romberg tableau uses the input delta.
    double current_step_size =
        delta * pow(options.ridders_step_shrink_factor,
                    options.max_num_ridders_extrapolations / 2);

    // Double-buffering temporary differential candidate vectors
    // from previous step size.
    ResidualCandidateMatrix stepsize_candidates_a(
        num_residuals, options.max_num_ridders_extrapolations);
    ResidualCandidateMatrix stepsize_candidates_b(
        num_residuals, options.max_num_ridders_extrapolations);
    ResidualCandidateMatrix* current_candidates = &stepsize_candidates_a;
    ResidualCandidateMatrix* previous_candidates = &stepsize_candidates_b;

    // Represents the computational error of the derivative. This variable is
    // initially set to a large value, and is set to the difference between
    // current and previous finite difference extrapolations.
    // norm_error is supposed to decrease as the finite difference tableau
    // generation progresses, serving both as an estimate for differentiation
    // error and as a measure of differentiation numerical stability.
    double norm_error = (std::numeric_limits<double>::max)();

    // Loop over decreasing step sizes until:
    //  1. Error is smaller than a given value (ridders_epsilon),
    //  2. Maximal order of extrapolation reached, or
    //  3. Extrapolation becomes numerically unstable.
    for (int i = 0; i < options.max_num_ridders_extrapolations; ++i) {
      // Compute the numerical derivative at this step size.
      if (!EvaluateJacobianColumn(functor,
                                  parameter_index,
                                  current_step_size,
                                  num_residuals,
                                  parameter_block_size,
                                  x.data(),
                                  residuals_at_eval_point,
                                  parameters,
                                  x_plus_delta.data(),
                                  temp_residuals.data(),
                                  current_candidates->col(0).data())) {
        // Something went wrong; bail.
        return false;
      }

      // Store initial results.
      if (i == 0) {
        residuals = current_candidates->col(0);
      }

      // Shrink differentiation step size.
      current_step_size /= options.ridders_step_shrink_factor;

      // Extrapolation factor for Richardson acceleration method (see below).
      double richardson_factor = options.ridders_step_shrink_factor *
                                 options.ridders_step_shrink_factor;
      for (int k = 1; k <= i; ++k) {
        // Extrapolate the various orders of finite differences using
        // the Richardson acceleration method.
        current_candidates->col(k) =
            (richardson_factor * current_candidates->col(k - 1) -
             previous_candidates->col(k - 1)) /
            (richardson_factor - 1.0);

        richardson_factor *= options.ridders_step_shrink_factor *
                             options.ridders_step_shrink_factor;

        // Compute the difference between the previous value and the current.
        double candidate_error = (std::max)(
            (current_candidates->col(k) - current_candidates->col(k - 1))
                .norm(),
            (current_candidates->col(k) - previous_candidates->col(k - 1))
                .norm());

        // If the error has decreased, update results.
        if (candidate_error <= norm_error) {
          norm_error = candidate_error;
          residuals = current_candidates->col(k);

          // If the error is small enough, stop.
          if (norm_error < options.ridders_epsilon) {
            break;
          }
        }
      }

      // After breaking out of the inner loop, declare convergence.
      if (norm_error < options.ridders_epsilon) {
        break;
      }

      // Check to see if the current gradient estimate is numerically unstable.
      // If so, bail out and return the last stable result.
      if (i > 0) {
        double tableau_error =
            (current_candidates->col(i) - previous_candidates->col(i - 1))
                .norm();

        // Compare current error to the chosen candidate's error.
        if (tableau_error >= 2 * norm_error) {
          break;
        }
      }

      std::swap(current_candidates, previous_candidates);
    }
    return true;
  }

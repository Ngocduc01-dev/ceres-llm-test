// u1504 – ceres::internal::WolfeLineSearch::ZoomPhase
// Trích từ internal/ceres/line_search.cc, dòng 698–881 (chỉ để xem, không compile)

bool WolfeLineSearch::ZoomPhase(const FunctionSample& initial_position,
                                FunctionSample bracket_low,
                                FunctionSample bracket_high,
                                FunctionSample* solution,
                                Summary* summary) const {
  LineSearchFunction* function = options().function;

  CHECK(bracket_low.value_is_valid && bracket_low.gradient_is_valid)
      << std::scientific << std::setprecision(kErrorMessageNumericPrecision)
      << "Ceres bug: f_low input to Wolfe Zoom invalid, please contact "
      << "the developers!, initial_position: " << initial_position
      << ", bracket_low: " << bracket_low << ", bracket_high: " << bracket_high;
  // We do not require bracket_high.gradient_is_valid as the gradient condition
  // for a valid bracket is only dependent upon bracket_low.gradient, and
  // in order to minimize jacobian evaluations, bracket_high.gradient may
  // not have been calculated (if bracket_high.value does not satisfy the
  // Armijo sufficient decrease condition and interpolation method does not
  // require it).
  //
  // We also do not require that: bracket_low.value < bracket_high.value,
  // although this is typical. This is to deal with the case when
  // bracket_low = initial_position, bracket_high is the first sample,
  // and bracket_high does not satisfy the Armijo condition, but still has
  // bracket_high.value < initial_position.value.
  CHECK(bracket_high.value_is_valid)
      << std::scientific << std::setprecision(kErrorMessageNumericPrecision)
      << "Ceres bug: f_high input to Wolfe Zoom invalid, please "
      << "contact the developers!, initial_position: " << initial_position
      << ", bracket_low: " << bracket_low << ", bracket_high: " << bracket_high;

  if (bracket_low.gradient * (bracket_high.x - bracket_low.x) >= 0) {
    // The third condition for a valid initial bracket:
    //
    //   3. bracket_high is chosen after bracket_low, s.t.
    //      bracket_low.gradient * (bracket_high.x - bracket_low.x) < 0.
    //
    // is not satisfied.  As this can happen when the users' cost function
    // returns inconsistent gradient values relative to the function values,
    // we do not CHECK_LT(), but we do stop processing and return an invalid
    // value.
    summary->error = StringPrintf(
        "Line search failed: Wolfe zoom phase passed a bracket "
        "which does not satisfy: bracket_low.gradient * "
        "(bracket_high.x - bracket_low.x) < 0 [%.8e !< 0] "
        "with initial_position: %s, bracket_low: %s, bracket_high:"
        " %s, the most likely cause of which is the cost function "
        "returning inconsistent gradient & function values.",
        bracket_low.gradient * (bracket_high.x - bracket_low.x),
        initial_position.ToDebugString().c_str(),
        bracket_low.ToDebugString().c_str(),
        bracket_high.ToDebugString().c_str());
    if (!options().is_silent) {
      LOG(WARNING) << summary->error;
    }
    solution->value_is_valid = false;
    return false;
  }

  const int num_bracketing_iterations = summary->num_iterations;
  const double descent_direction_max_norm = function->DirectionInfinityNorm();

  while (true) {
    // Set solution to bracket_low, as it is our best step size (smallest f())
    // found thus far and satisfies the Armijo condition, even though it does
    // not satisfy the Wolfe condition.
    *solution = bracket_low;
    if (summary->num_iterations >= options().max_num_iterations) {
      summary->error = StringPrintf(
          "Line search failed: Wolfe zoom phase failed to "
          "find a point satisfying strong Wolfe conditions "
          "within specified max_num_iterations: %d, "
          "(num iterations taken for bracketing: %d).",
          options().max_num_iterations,
          num_bracketing_iterations);
      if (!options().is_silent) {
        LOG(WARNING) << summary->error;
      }
      return false;
    }
    if (fabs(bracket_high.x - bracket_low.x) * descent_direction_max_norm <
        options().min_step_size) {
      // Bracket width has been reduced below tolerance, and no point satisfying
      // the strong Wolfe conditions has been found.
      summary->error = StringPrintf(
          "Line search failed: Wolfe zoom bracket width: %.5e "
          "too small with descent_direction_max_norm: %.5e.",
          fabs(bracket_high.x - bracket_low.x),
          descent_direction_max_norm);
      if (!options().is_silent) {
        LOG(WARNING) << summary->error;
      }
      return false;
    }

    ++summary->num_iterations;
    // Polynomial interpolation requires inputs ordered according to step size,
    // not f(step size).
    const FunctionSample& lower_bound_step =
        bracket_low.x < bracket_high.x ? bracket_low : bracket_high;
    const FunctionSample& upper_bound_step =
        bracket_low.x < bracket_high.x ? bracket_high : bracket_low;
    // We are performing 2-point interpolation only here, but the API of
    // InterpolatingPolynomialMinimizingStepSize() allows for up to
    // 3-point interpolation, so pad call with a sample with an invalid
    // value that will therefore be ignored.
    const FunctionSample unused_previous;
    DCHECK(!unused_previous.value_is_valid);
    const double polynomial_minimization_start_time = WallTimeInSeconds();
    const double step_size = this->InterpolatingPolynomialMinimizingStepSize(
        options().interpolation_type,
        lower_bound_step,
        unused_previous,
        upper_bound_step,
        lower_bound_step.x,
        upper_bound_step.x);
    summary->polynomial_minimization_time_in_seconds +=
        (WallTimeInSeconds() - polynomial_minimization_start_time);
    // No check on magnitude of step size being too small here as it is
    // lower-bounded by the initial bracket start point, which was valid.
    //
    // As we require the gradient to evaluate the Wolfe condition, we always
    // calculate it together with the value, irrespective of the interpolation
    // type.  As opposed to only calculating the gradient after the Armijo
    // condition is satisfied, as the computational saving from this approach
    // would be slight (perhaps even negative due to the extra call).  Also,
    // always calculating the value & gradient together protects against us
    // reporting invalid solutions if the cost function returns slightly
    // different function values when evaluated with / without gradients (due
    // to numerical issues).
    ++summary->num_function_evaluations;
    ++summary->num_gradient_evaluations;
    const bool kEvaluateGradient = true;
    function->Evaluate(step_size, kEvaluateGradient, solution);
    if (!solution->value_is_valid || !solution->gradient_is_valid) {
      summary->error = StringPrintf(
          "Line search failed: Wolfe Zoom phase found "
          "step_size: %.5e, for which function is invalid, "
          "between low_step: %.5e and high_step: %.5e "
          "at which function is valid.",
          solution->x,
          bracket_low.x,
          bracket_high.x);
      if (!options().is_silent) {
        LOG(WARNING) << summary->error;
      }
      return false;
    }

    VLOG(3) << "Zoom iteration: "
            << summary->num_iterations - num_bracketing_iterations
            << ", bracket_low: " << bracket_low
            << ", bracket_high: " << bracket_high
            << ", minimizing solution: " << *solution;

    if ((solution->value > (initial_position.value +
                            options().sufficient_decrease *
                                initial_position.gradient * solution->x)) ||
        (solution->value >= bracket_low.value)) {
      // Armijo sufficient decrease not satisfied, or not better
      // than current lowest sample, use as new upper bound.
      bracket_high = *solution;
      continue;
    }

    // Armijo sufficient decrease satisfied, check strong Wolfe condition.
    if (fabs(solution->gradient) <=
        -options().sufficient_curvature_decrease * initial_position.gradient) {
      // Found a valid termination point satisfying strong Wolfe conditions.
      VLOG(3) << std::scientific
              << std::setprecision(kErrorMessageNumericPrecision)
              << "Zoom phase found step size: " << solution->x
              << ", satisfying strong Wolfe conditions.";
      break;

    } else if (solution->gradient * (bracket_high.x - bracket_low.x) >= 0) {
      bracket_high = bracket_low;
    }

    bracket_low = *solution;
  }
  // Solution contains a valid point which satisfies the strong Wolfe
  // conditions.
  return true;
}

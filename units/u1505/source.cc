// u1505 – ceres::internal::WolfeLineSearch::BracketingPhase
// Trích từ internal/ceres/line_search.cc, dòng 499–692 (chỉ để xem, không compile)

bool WolfeLineSearch::BracketingPhase(const FunctionSample& initial_position,
                                      const double step_size_estimate,
                                      FunctionSample* bracket_low,
                                      FunctionSample* bracket_high,
                                      bool* do_zoom_search,
                                      Summary* summary) const {
  LineSearchFunction* function = options().function;

  FunctionSample previous = initial_position;
  FunctionSample current;

  const double descent_direction_max_norm = function->DirectionInfinityNorm();

  *do_zoom_search = false;
  *bracket_low = initial_position;

  // As we require the gradient to evaluate the Wolfe condition, we always
  // calculate it together with the value, irrespective of the interpolation
  // type.  As opposed to only calculating the gradient after the Armijo
  // condition is satisfied, as the computational saving from this approach
  // would be slight (perhaps even negative due to the extra call).  Also,
  // always calculating the value & gradient together protects against us
  // reporting invalid solutions if the cost function returns slightly different
  // function values when evaluated with / without gradients (due to numerical
  // issues).
  ++summary->num_function_evaluations;
  ++summary->num_gradient_evaluations;
  const bool kEvaluateGradient = true;
  function->Evaluate(step_size_estimate, kEvaluateGradient, &current);
  while (true) {
    ++summary->num_iterations;

    if (current.value_is_valid &&
        (current.value > (initial_position.value +
                          options().sufficient_decrease *
                              initial_position.gradient * current.x) ||
         (previous.value_is_valid && current.value > previous.value))) {
      // Bracket found: current step size violates Armijo sufficient decrease
      // condition, or has stepped past an inflection point of f() relative to
      // previous step size.
      *do_zoom_search = true;
      *bracket_low = previous;
      *bracket_high = current;
      VLOG(3) << std::scientific
              << std::setprecision(kErrorMessageNumericPrecision)
              << "Bracket found: current step (" << current.x
              << ") violates Armijo sufficient condition, or has passed an "
              << "inflection point of f() based on value.";
      break;
    }

    if (current.value_is_valid &&
        fabs(current.gradient) <= -options().sufficient_curvature_decrease *
                                      initial_position.gradient) {
      // Current step size satisfies the strong Wolfe conditions, and is thus a
      // valid termination point, therefore a Zoom not required.
      *bracket_low = current;
      *bracket_high = current;
      VLOG(3) << std::scientific
              << std::setprecision(kErrorMessageNumericPrecision)
              << "Bracketing phase found step size: " << current.x
              << ", satisfying strong Wolfe conditions, initial_position: "
              << initial_position << ", current: " << current;
      break;

    } else if (current.value_is_valid && current.gradient >= 0) {
      // Bracket found: current step size has stepped past an inflection point
      // of f(), but Armijo sufficient decrease is still satisfied and
      // f(current) is our best minimum thus far.  Remember step size
      // monotonically increases, thus previous_step_size < current_step_size
      // even though f(previous) > f(current).
      *do_zoom_search = true;
      // Note inverse ordering from first bracket case.
      *bracket_low = current;
      *bracket_high = previous;
      VLOG(3) << "Bracket found: current step (" << current.x
              << ") satisfies Armijo, but has gradient >= 0, thus have passed "
              << "an inflection point of f().";
      break;

    } else if (current.value_is_valid &&
               fabs(current.x - previous.x) * descent_direction_max_norm <
                   options().min_step_size) {
      // We have shrunk the search bracket to a width less than our tolerance,
      // and still not found either a point satisfying the strong Wolfe
      // conditions, or a valid bracket containing such a point. Stop searching
      // and set bracket_low to the size size amongst all those tested which
      // minimizes f() and satisfies the Armijo condition.

      if (!options().is_silent) {
        LOG(WARNING) << "Line search failed: Wolfe bracketing phase shrank "
                     << "bracket width: " << fabs(current.x - previous.x)
                     << ", to < tolerance: " << options().min_step_size
                     << ", with descent_direction_max_norm: "
                     << descent_direction_max_norm << ", and failed to find "
                     << "a point satisfying the strong Wolfe conditions or a "
                     << "bracketing containing such a point. Accepting "
                     << "point found satisfying Armijo condition only, to "
                     << "allow continuation.";
      }
      *bracket_low = current;
      break;

    } else if (summary->num_iterations >= options().max_num_iterations) {
      // Check num iterations bound here so that we always evaluate the
      // max_num_iterations-th iteration against all conditions, and
      // then perform no additional (unused) evaluations.
      summary->error = StringPrintf(
          "Line search failed: Wolfe bracketing phase failed to "
          "find a point satisfying strong Wolfe conditions, or a "
          "bracket containing such a point within specified "
          "max_num_iterations: %d",
          options().max_num_iterations);
      if (!options().is_silent) {
        LOG(WARNING) << summary->error;
      }
      // Ensure that bracket_low is always set to the step size amongst all
      // those tested which minimizes f() and satisfies the Armijo condition
      // when we terminate due to the 'artificial' max_num_iterations condition.
      *bracket_low =
          current.value_is_valid && current.value < bracket_low->value
              ? current
              : *bracket_low;
      break;
    }
    // Either: f(current) is invalid; or, f(current) is valid, but does not
    // satisfy the strong Wolfe conditions itself, or the conditions for
    // being a boundary of a bracket.

    // If f(current) is valid, (but meets no criteria) expand the search by
    // increasing the step size.  If f(current) is invalid, contract the step
    // size.
    //
    // In Nocedal & Wright [1] (p60), the step-size can only increase in the
    // bracketing phase: step_size_{k+1} \in [step_size_k, step_size_k *
    // factor]. However this does not account for the function returning invalid
    // values which we support, in which case we need to contract the step size
    // whilst ensuring that we do not invert the bracket, i.e, we require that:
    // step_size_{k-1} <= step_size_{k+1} < step_size_k.
    const double min_step_size =
        current.value_is_valid ? current.x : previous.x;
    const double max_step_size =
        current.value_is_valid ? (current.x * options().max_step_expansion)
                               : current.x;

    // We are performing 2-point interpolation only here, but the API of
    // InterpolatingPolynomialMinimizingStepSize() allows for up to
    // 3-point interpolation, so pad call with a sample with an invalid
    // value that will therefore be ignored.
    const FunctionSample unused_previous;
    DCHECK(!unused_previous.value_is_valid);
    // Contracts step size if f(current) is not valid.
    const double polynomial_minimization_start_time = WallTimeInSeconds();
    const double step_size = this->InterpolatingPolynomialMinimizingStepSize(
        options().interpolation_type,
        previous,
        unused_previous,
        current,
        min_step_size,
        max_step_size);
    summary->polynomial_minimization_time_in_seconds +=
        (WallTimeInSeconds() - polynomial_minimization_start_time);
    if (step_size * descent_direction_max_norm < options().min_step_size) {
      summary->error = StringPrintf(
          "Line search failed: step_size too small: %.5e "
          "with descent_direction_max_norm: %.5e",
          step_size,
          descent_direction_max_norm);
      if (!options().is_silent) {
        LOG(WARNING) << summary->error;
      }
      return false;
    }

    // Only advance the lower boundary (in x) of the bracket if f(current)
    // is valid such that we can support contracting the step size when
    // f(current) is invalid without risking inverting the bracket in x, i.e.
    // prevent previous.x > current.x.
    previous = current.value_is_valid ? current : previous;
    ++summary->num_function_evaluations;
    ++summary->num_gradient_evaluations;
    function->Evaluate(step_size, kEvaluateGradient, &current);
  }

  // Ensure that even if a valid bracket was found, we will only mark a zoom
  // as required if the bracket's width is greater than our minimum tolerance.
  if (*do_zoom_search &&
      fabs(bracket_high->x - bracket_low->x) * descent_direction_max_norm <
          options().min_step_size) {
    *do_zoom_search = false;
  }

  return true;
}

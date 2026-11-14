// u1522 – ceres::internal::WolfeLineSearch::DoSearch
// Trích từ internal/ceres/line_search.cc, dòng 370–481 (chỉ để xem, không compile)

void WolfeLineSearch::DoSearch(const double step_size_estimate,
                               const double initial_cost,
                               const double initial_gradient,
                               Summary* summary) const {
  // All parameters should have been validated by the Solver, but as
  // invalid values would produce crazy nonsense, hard check them here.
  CHECK_GE(step_size_estimate, 0.0);
  CHECK_GT(options().sufficient_decrease, 0.0);
  CHECK_GT(options().sufficient_curvature_decrease,
           options().sufficient_decrease);
  CHECK_LT(options().sufficient_curvature_decrease, 1.0);
  CHECK_GT(options().max_step_expansion, 1.0);

  // Note initial_cost & initial_gradient are evaluated at step_size = 0,
  // not step_size_estimate, which is our starting guess.
  FunctionSample initial_position(0.0, initial_cost, initial_gradient);
  initial_position.vector_x = options().function->position();
  initial_position.vector_x_is_valid = true;
  bool do_zoom_search = false;
  // Important: The high/low in bracket_high & bracket_low refer to their
  // _function_ values, not their step sizes i.e. it is _not_ required that
  // bracket_low.x < bracket_high.x.
  FunctionSample solution, bracket_low, bracket_high;

  // Wolfe bracketing phase: Increases step_size until either it finds a point
  // that satisfies the (strong) Wolfe conditions, or an interval that brackets
  // step sizes which satisfy the conditions.  From Nocedal & Wright [1] p61 the
  // interval: (step_size_{k-1}, step_size_{k}) contains step lengths satisfying
  // the strong Wolfe conditions if one of the following conditions are met:
  //
  //   1. step_size_{k} violates the sufficient decrease (Armijo) condition.
  //   2. f(step_size_{k}) >= f(step_size_{k-1}).
  //   3. f'(step_size_{k}) >= 0.
  //
  // Caveat: If f(step_size_{k}) is invalid, then step_size is reduced, ignoring
  // this special case, step_size monotonically increases during bracketing.
  if (!this->BracketingPhase(initial_position,
                             step_size_estimate,
                             &bracket_low,
                             &bracket_high,
                             &do_zoom_search,
                             summary)) {
    // Failed to find either a valid point, a valid bracket satisfying the Wolfe
    // conditions, or even a step size > minimum tolerance satisfying the Armijo
    // condition.
    return;
  }

  if (!do_zoom_search) {
    // Either: Bracketing phase already found a point satisfying the strong
    // Wolfe conditions, thus no Zoom required.
    //
    // Or: Bracketing failed to find a valid bracket or a point satisfying the
    // strong Wolfe conditions within max_num_iterations, or whilst searching
    // shrank the bracket width until it was below our minimum tolerance.
    // As these are 'artificial' constraints, and we would otherwise fail to
    // produce a valid point when ArmijoLineSearch would succeed, we return the
    // point with the lowest cost found thus far which satisfies the Armijo
    // condition (but not the Wolfe conditions).
    summary->optimal_point = bracket_low;
    summary->success = true;
    return;
  }

  VLOG(3) << std::scientific << std::setprecision(kErrorMessageNumericPrecision)
          << "Starting line search zoom phase with bracket_low: " << bracket_low
          << ", bracket_high: " << bracket_high
          << ", bracket width: " << fabs(bracket_low.x - bracket_high.x)
          << ", bracket abs delta cost: "
          << fabs(bracket_low.value - bracket_high.value);

  // Wolfe Zoom phase: Called when the Bracketing phase finds an interval of
  // non-zero, finite width that should bracket step sizes which satisfy the
  // (strong) Wolfe conditions (before finding a step size that satisfies the
  // conditions).  Zoom successively decreases the size of the interval until a
  // step size which satisfies the Wolfe conditions is found.  The interval is
  // defined by bracket_low & bracket_high, which satisfy:
  //
  //   1. The interval bounded by step sizes: bracket_low.x & bracket_high.x
  //      contains step sizes that satisfy the strong Wolfe conditions.
  //   2. bracket_low.x is of all the step sizes evaluated *which satisfied the
  //      Armijo sufficient decrease condition*, the one which generated the
  //      smallest function value, i.e. bracket_low.value <
  //      f(all other steps satisfying Armijo).
  //        - Note that this does _not_ (necessarily) mean that initially
  //          bracket_low.value < bracket_high.value (although this is typical)
  //          e.g. when bracket_low = initial_position, and bracket_high is the
  //          first sample, and which does not satisfy the Armijo condition,
  //          but still has bracket_high.value < initial_position.value.
  //   3. bracket_high is chosen after bracket_low, s.t.
  //      bracket_low.gradient * (bracket_high.x - bracket_low.x) < 0.
  if (!this->ZoomPhase(
          initial_position, bracket_low, bracket_high, &solution, summary) &&
      !solution.value_is_valid) {
    // Failed to find a valid point (given the specified decrease parameters)
    // within the specified bracket.
    return;
  }
  // Ensure that if we ran out of iterations whilst zooming the bracket, or
  // shrank the bracket width to < tolerance and failed to find a point which
  // satisfies the strong Wolfe curvature condition, that we return the point
  // amongst those found thus far, which minimizes f() and satisfies the Armijo
  // condition.

  if (!solution.value_is_valid || solution.value > bracket_low.value) {
    summary->optimal_point = bracket_low;
  } else {
    summary->optimal_point = solution;
  }

  summary->success = true;
}

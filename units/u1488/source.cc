// u1488 – ceres::internal::LineSearch::InterpolatingPolynomialMinimizingStepSize
// Trích từ internal/ceres/line_search.cc, dòng 209–275 (chỉ để xem, không compile)

double LineSearch::InterpolatingPolynomialMinimizingStepSize(
    const LineSearchInterpolationType& interpolation_type,
    const FunctionSample& lowerbound,
    const FunctionSample& previous,
    const FunctionSample& current,
    const double min_step_size,
    const double max_step_size) const {
  if (!current.value_is_valid ||
      (interpolation_type == BISECTION && max_step_size <= current.x)) {
    // Either: sample is invalid; or we are using BISECTION and contracting
    // the step size.
    return std::min(std::max(current.x * 0.5, min_step_size), max_step_size);
  } else if (interpolation_type == BISECTION) {
    CHECK_GT(max_step_size, current.x);
    // We are expanding the search (during a Wolfe bracketing phase) using
    // BISECTION interpolation.  Using BISECTION when trying to expand is
    // strictly speaking an oxymoron, but we define this to mean always taking
    // the maximum step size so that the Armijo & Wolfe implementations are
    // agnostic to the interpolation type.
    return max_step_size;
  }
  // Only check if lower-bound is valid here, where it is required
  // to avoid replicating current.value_is_valid == false
  // behaviour in WolfeLineSearch.
  CHECK(lowerbound.value_is_valid)
      << std::scientific << std::setprecision(kErrorMessageNumericPrecision)
      << "Ceres bug: lower-bound sample for interpolation is invalid, "
      << "please contact the developers!, interpolation_type: "
      << LineSearchInterpolationTypeToString(interpolation_type)
      << ", lowerbound: " << lowerbound << ", previous: " << previous
      << ", current: " << current;

  // Select step size by interpolating the function and gradient values
  // and minimizing the corresponding polynomial.
  std::vector<FunctionSample> samples;
  samples.push_back(lowerbound);

  if (interpolation_type == QUADRATIC) {
    // Two point interpolation using function values and the
    // gradient at the lower bound.
    samples.emplace_back(current.x, current.value);

    if (previous.value_is_valid) {
      // Three point interpolation, using function values and the
      // gradient at the lower bound.
      samples.emplace_back(previous.x, previous.value);
    }
  } else if (interpolation_type == CUBIC) {
    // Two point interpolation using the function values and the gradients.
    samples.push_back(current);

    if (previous.value_is_valid) {
      // Three point interpolation using the function values and
      // the gradients.
      samples.push_back(previous);
    }
  } else {
    LOG(FATAL) << "Ceres bug: No handler for interpolation_type: "
               << LineSearchInterpolationTypeToString(interpolation_type)
               << ", please contact the developers!";
  }

  double step_size = 0.0, unused_min_value = 0.0;
  MinimizeInterpolatingPolynomial(
      samples, min_step_size, max_step_size, &step_size, &unused_min_value);
  return step_size;
}

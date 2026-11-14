// u1314 – ceres::internal::DoglegStrategy::FindMinimumOnTrustRegionBoundary
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 472–514 (chỉ để xem, không compile)

bool DoglegStrategy::FindMinimumOnTrustRegionBoundary(Vector2d* minimum) const {
  CHECK(minimum != nullptr);

  // Return (0, 0) in all error cases.
  minimum->setZero();

  // Create the fourth-degree polynomial that is a necessary condition for
  // optimality.
  const Vector polynomial = MakePolynomialForBoundaryConstrainedProblem();

  // Find the real parts y_i of its roots (not only the real roots).
  Vector roots_real;
  if (!FindPolynomialRoots(polynomial, &roots_real, nullptr)) {
    // Failed to find the roots of the polynomial, i.e. the candidate
    // solutions of the constrained problem. Report this back to the caller.
    return false;
  }

  // For each root y, compute B x(y) and check for feasibility.
  // Notice that there should always be four roots, as the leading term of
  // the polynomial is r^2 and therefore non-zero. However, as some roots
  // may be complex, the real parts are not necessarily unique.
  double minimum_value = std::numeric_limits<double>::max();
  bool valid_root_found = false;
  for (int i = 0; i < roots_real.size(); ++i) {
    const Vector2d x_i = ComputeSubspaceStepFromRoot(roots_real(i));

    // Not all roots correspond to points on the trust region boundary.
    // There are at most four candidate solutions. As we are interested
    // in the minimum, it is safe to consider all of them after projecting
    // them onto the trust region boundary.
    if (x_i.norm() > 0) {
      const double f_i = EvaluateSubspaceModel((radius_ / x_i.norm()) * x_i);
      valid_root_found = true;
      if (f_i < minimum_value) {
        minimum_value = f_i;
        *minimum = x_i;
      }
    }
  }

  return valid_root_found;
}

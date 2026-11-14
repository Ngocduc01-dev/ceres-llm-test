// u1395 – ceres::internal::DoglegStrategy::ComputeSubspaceDoglegStep
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 265–365 (chỉ để xem, không compile)

void DoglegStrategy::ComputeSubspaceDoglegStep(double* dogleg) {
  VectorRef dogleg_step(dogleg, gradient_.rows());

  // The Gauss-Newton point is inside the trust region if |GN| <= radius_.
  // This test is valid even though radius_ is a length in the two-dimensional
  // subspace while gauss_newton_step_ is expressed in the (scaled)
  // higher dimensional original space. This is because
  //
  //   1. gauss_newton_step_ by definition lies in the subspace, and
  //   2. the subspace basis is orthonormal.
  //
  // As a consequence, the norm of the gauss_newton_step_ in the subspace is
  // the same as its norm in the original space.
  const double gauss_newton_norm = gauss_newton_step_.norm();
  if (gauss_newton_norm <= radius_) {
    dogleg_step = gauss_newton_step_;
    dogleg_step_norm_ = gauss_newton_norm;
    dogleg_step.array() /= diagonal_.array();
    VLOG(3) << "GaussNewton step size: " << dogleg_step_norm_
            << " radius: " << radius_;
    return;
  }

  // The optimum lies on the boundary of the trust region. The above problem
  // therefore becomes
  //
  //   min. 1/2 x^T B^T H B x + g^T B x
  //   s.t. || B x ||^2 = r^2
  //
  // Notice the equality in the constraint.
  //
  // This can be solved by forming the Lagrangian, solving for x(y), where
  // y is the Lagrange multiplier, using the gradient of the objective, and
  // putting x(y) back into the constraint. This results in a fourth order
  // polynomial in y, which can be solved using e.g. the companion matrix.
  // See the description of MakePolynomialForBoundaryConstrainedProblem for
  // details. The result is up to four real roots y*, not all of which
  // correspond to feasible points. The feasible points x(y*) have to be
  // tested for optimality.

  if (subspace_is_one_dimensional_) {
    // The subspace is one-dimensional, so both the gradient and
    // the Gauss-Newton step point towards the same direction.
    // In this case, we move along the gradient until we reach the trust
    // region boundary.
    dogleg_step = -(radius_ / gradient_.norm()) * gradient_;
    dogleg_step_norm_ = radius_;
    dogleg_step.array() /= diagonal_.array();
    VLOG(3) << "Dogleg subspace step size (1D): " << dogleg_step_norm_
            << " radius: " << radius_;
    return;
  }

  Vector2d minimum(0.0, 0.0);
  if (!FindMinimumOnTrustRegionBoundary(&minimum)) {
    // For the positive semi-definite case, a traditional dogleg step
    // is taken in this case.
    LOG(WARNING) << "Failed to compute polynomial roots. "
                 << "Taking traditional dogleg step instead.";
    ComputeTraditionalDoglegStep(dogleg);
    return;
  }

  // Test first order optimality at the minimum.
  // The first order KKT conditions state that the minimum x*
  // has to satisfy either || x* ||^2 < r^2 (i.e. has to lie within
  // the trust region), or
  //
  //   (B x* + g) + y x* = 0
  //
  // for some positive scalar y.
  // Here, as it is already known that the minimum lies on the boundary, the
  // latter condition is tested. To allow for small imprecisions, we test if
  // the angle between (B x* + g) and -x* is smaller than acos(0.99).
  // The exact value of the cosine is arbitrary but should be close to 1.
  //
  // This condition should not be violated. If it is, the minimum was not
  // correctly determined.
  const double kCosineThreshold = 0.99;
  const Vector2d grad_minimum = subspace_B_ * minimum + subspace_g_;
  const double cosine_angle =
      -minimum.dot(grad_minimum) / (minimum.norm() * grad_minimum.norm());
  if (cosine_angle < kCosineThreshold) {
    LOG(WARNING) << "First order optimality seems to be violated "
                 << "in the subspace method!\n"
                 << "Cosine of angle between x and B x + g is " << cosine_angle
                 << ".\n"
                 << "Taking a regular dogleg step instead.\n"
                 << "Please consider filing a bug report if this "
                 << "happens frequently or consistently.\n";
    ComputeTraditionalDoglegStep(dogleg);
    return;
  }

  // Create the full step from the optimal 2d solution.
  dogleg_step = subspace_basis_ * minimum;
  dogleg_step_norm_ = radius_;
  dogleg_step.array() /= diagonal_.array();
  VLOG(3) << "Dogleg subspace step size: " << dogleg_step_norm_
          << " radius: " << radius_;
}

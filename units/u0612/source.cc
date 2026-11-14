// u0612 – ceres::internal::DoglegStrategy::ComputeTraditionalDoglegStep
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 200–254 (chỉ để xem, không compile)

void DoglegStrategy::ComputeTraditionalDoglegStep(double* dogleg) {
  VectorRef dogleg_step(dogleg, gradient_.rows());

  // Case 1. The Gauss-Newton step lies inside the trust region, and
  // is therefore the optimal solution to the trust-region problem.
  const double gradient_norm = gradient_.norm();
  const double gauss_newton_norm = gauss_newton_step_.norm();
  if (gauss_newton_norm <= radius_) {
    dogleg_step = gauss_newton_step_;
    dogleg_step_norm_ = gauss_newton_norm;
    dogleg_step.array() /= diagonal_.array();
    VLOG(3) << "GaussNewton step size: " << dogleg_step_norm_
            << " radius: " << radius_;
    return;
  }

  // Case 2. The Cauchy point and the Gauss-Newton steps lie outside
  // the trust region. Rescale the Cauchy point to the trust region
  // and return.
  if (gradient_norm * alpha_ >= radius_) {
    dogleg_step = -(radius_ / gradient_norm) * gradient_;
    dogleg_step_norm_ = radius_;
    dogleg_step.array() /= diagonal_.array();
    VLOG(3) << "Cauchy step size: " << dogleg_step_norm_
            << " radius: " << radius_;
    return;
  }

  // Case 3. The Cauchy point is inside the trust region and the
  // Gauss-Newton step is outside. Compute the line joining the two
  // points and the point on it which intersects the trust region
  // boundary.

  // a = alpha * -gradient
  // b = gauss_newton_step
  const double b_dot_a = -alpha_ * gradient_.dot(gauss_newton_step_);
  const double a_squared_norm = pow(alpha_ * gradient_norm, 2.0);
  const double b_minus_a_squared_norm =
      a_squared_norm - 2 * b_dot_a + pow(gauss_newton_norm, 2);

  // c = a' (b - a)
  //   = alpha * -gradient' gauss_newton_step - alpha^2 |gradient|^2
  const double c = b_dot_a - a_squared_norm;
  const double d = sqrt(c * c + b_minus_a_squared_norm *
                                    (pow(radius_, 2.0) - a_squared_norm));

  double beta = (c <= 0) ? (d - c) / b_minus_a_squared_norm
                         : (radius_ * radius_ - a_squared_norm) / (d + c);
  dogleg_step =
      (-alpha_ * (1.0 - beta)) * gradient_ + beta * gauss_newton_step_;
  dogleg_step_norm_ = dogleg_step.norm();
  dogleg_step.array() /= diagonal_.array();
  VLOG(3) << "Dogleg step size: " << dogleg_step_norm_
          << " radius: " << radius_;
}

// u0596 – ceres::(anonymous)::QuaternionPlusImpl
// Trích từ internal/ceres/manifold.cc, dòng 27–60 (chỉ để xem, không compile)

template <typename Order>
inline void QuaternionPlusImpl(const double* x,
                               const double* delta,
                               double* x_plus_delta) {
  // x_plus_delta = QuaternionProduct(q_delta, x), where q_delta is the
  // quaternion constructed from delta.
  const double norm_delta = std::hypot(delta[0], delta[1], delta[2]);

  if (std::fpclassify(norm_delta) == FP_ZERO) {
    // No change in rotation: return the quaternion as is.
    std::copy_n(x, 4, x_plus_delta);
    return;
  }

  const double sin_delta_by_delta = (std::sin(norm_delta) / norm_delta);
  double q_delta[4];
  q_delta[Order::kW] = std::cos(norm_delta);
  q_delta[Order::kX] = sin_delta_by_delta * delta[0];
  q_delta[Order::kY] = sin_delta_by_delta * delta[1];
  q_delta[Order::kZ] = sin_delta_by_delta * delta[2];

  x_plus_delta[Order::kW] =
      q_delta[Order::kW] * x[Order::kW] - q_delta[Order::kX] * x[Order::kX] -
      q_delta[Order::kY] * x[Order::kY] - q_delta[Order::kZ] * x[Order::kZ];
  x_plus_delta[Order::kX] =
      q_delta[Order::kW] * x[Order::kX] + q_delta[Order::kX] * x[Order::kW] +
      q_delta[Order::kY] * x[Order::kZ] - q_delta[Order::kZ] * x[Order::kY];
  x_plus_delta[Order::kY] =
      q_delta[Order::kW] * x[Order::kY] - q_delta[Order::kX] * x[Order::kZ] +
      q_delta[Order::kY] * x[Order::kW] + q_delta[Order::kZ] * x[Order::kX];
  x_plus_delta[Order::kZ] =
      q_delta[Order::kW] * x[Order::kZ] + q_delta[Order::kX] * x[Order::kY] -
      q_delta[Order::kY] * x[Order::kX] + q_delta[Order::kZ] * x[Order::kW];
}

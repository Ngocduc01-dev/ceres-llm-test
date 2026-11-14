// u0597 – ceres::(anonymous)::QuaternionMinusImpl
// Trích từ internal/ceres/manifold.cc, dòng 81–112 (chỉ để xem, không compile)

template <typename Order>
inline void QuaternionMinusImpl(const double* y,
                                const double* x,
                                double* y_minus_x) {
  // ambient_y_minus_x = QuaternionProduct(y, -x) where -x is the conjugate of
  // x.
  double ambient_y_minus_x[4];
  ambient_y_minus_x[Order::kW] =
      y[Order::kW] * x[Order::kW] + y[Order::kX] * x[Order::kX] +
      y[Order::kY] * x[Order::kY] + y[Order::kZ] * x[Order::kZ];
  ambient_y_minus_x[Order::kX] =
      -y[Order::kW] * x[Order::kX] + y[Order::kX] * x[Order::kW] -
      y[Order::kY] * x[Order::kZ] + y[Order::kZ] * x[Order::kY];
  ambient_y_minus_x[Order::kY] =
      -y[Order::kW] * x[Order::kY] + y[Order::kX] * x[Order::kZ] +
      y[Order::kY] * x[Order::kW] - y[Order::kZ] * x[Order::kX];
  ambient_y_minus_x[Order::kZ] =
      -y[Order::kW] * x[Order::kZ] - y[Order::kX] * x[Order::kY] +
      y[Order::kY] * x[Order::kX] + y[Order::kZ] * x[Order::kW];

  const double u_norm = std::hypot(ambient_y_minus_x[Order::kX],
                                   ambient_y_minus_x[Order::kY],
                                   ambient_y_minus_x[Order::kZ]);
  if (std::fpclassify(u_norm) != FP_ZERO) {
    const double theta = std::atan2(u_norm, ambient_y_minus_x[Order::kW]);
    y_minus_x[0] = theta * ambient_y_minus_x[Order::kX] / u_norm;
    y_minus_x[1] = theta * ambient_y_minus_x[Order::kY] / u_norm;
    y_minus_x[2] = theta * ambient_y_minus_x[Order::kZ] / u_norm;
  } else {
    std::fill_n(y_minus_x, 3, 0.0);
  }
}

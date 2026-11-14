// u0582 – ceres::(anonymous)::QuaternionMinusJacobianImpl
// Trích từ internal/ceres/manifold.cc, dòng 114–131 (chỉ để xem, không compile)

template <typename Order>
inline void QuaternionMinusJacobianImpl(const double* x, double* jacobian_ptr) {
  Eigen::Map<Eigen::Matrix<double, 3, 4, Eigen::RowMajor>> jacobian(
      jacobian_ptr);

  jacobian(0, Order::kW) = -x[Order::kX];
  jacobian(0, Order::kX) = x[Order::kW];
  jacobian(0, Order::kY) = -x[Order::kZ];
  jacobian(0, Order::kZ) = x[Order::kY];
  jacobian(1, Order::kW) = -x[Order::kY];
  jacobian(1, Order::kX) = x[Order::kZ];
  jacobian(1, Order::kY) = x[Order::kW];
  jacobian(1, Order::kZ) = -x[Order::kX];
  jacobian(2, Order::kW) = -x[Order::kZ];
  jacobian(2, Order::kX) = -x[Order::kY];
  jacobian(2, Order::kY) = x[Order::kX];
  jacobian(2, Order::kZ) = x[Order::kW];
}

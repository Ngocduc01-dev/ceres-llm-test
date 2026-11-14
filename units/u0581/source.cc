// u0581 – ceres::(anonymous)::QuaternionPlusJacobianImpl
// Trích từ internal/ceres/manifold.cc, dòng 62–79 (chỉ để xem, không compile)

template <typename Order>
inline void QuaternionPlusJacobianImpl(const double* x, double* jacobian_ptr) {
  Eigen::Map<Eigen::Matrix<double, 4, 3, Eigen::RowMajor>> jacobian(
      jacobian_ptr);

  jacobian(Order::kW, 0) = -x[Order::kX];
  jacobian(Order::kW, 1) = -x[Order::kY];
  jacobian(Order::kW, 2) = -x[Order::kZ];
  jacobian(Order::kX, 0) = x[Order::kW];
  jacobian(Order::kX, 1) = x[Order::kZ];
  jacobian(Order::kX, 2) = -x[Order::kY];
  jacobian(Order::kY, 0) = -x[Order::kZ];
  jacobian(Order::kY, 1) = x[Order::kW];
  jacobian(Order::kY, 2) = x[Order::kX];
  jacobian(Order::kZ, 0) = x[Order::kY];
  jacobian(Order::kZ, 1) = -x[Order::kX];
  jacobian(Order::kZ, 2) = x[Order::kW];
}

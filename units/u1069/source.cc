// u1069 – ceres::ProductManifold::MinusJacobian
// Trích từ include/ceres/product_manifold.h, dòng 126–133 (chỉ để xem, không compile)

  bool MinusJacobian(const double* x, double* jacobian_ptr) const override {
    MatrixRef jacobian(jacobian_ptr, TangentSize(), AmbientSize());
    jacobian.setZero();
    internal::FixedArray<double> buffer(buffer_size_);

    return MinusJacobianImpl(
        x, jacobian, buffer, std::make_index_sequence<kNumManifolds>{});
  }

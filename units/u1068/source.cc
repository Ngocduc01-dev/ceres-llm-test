// u1068 – ceres::ProductManifold::PlusJacobian
// Trích từ include/ceres/product_manifold.h, dòng 117–124 (chỉ để xem, không compile)

  bool PlusJacobian(const double* x, double* jacobian_ptr) const override {
    MatrixRef jacobian(jacobian_ptr, AmbientSize(), TangentSize());
    jacobian.setZero();
    internal::FixedArray<double> buffer(buffer_size_);

    return PlusJacobianImpl(
        x, jacobian, buffer, std::make_index_sequence<kNumManifolds>{});
  }

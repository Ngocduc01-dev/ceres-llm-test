// u0181 – ceres::EuclideanManifold::PlusJacobian
// Trích từ include/ceres/manifold.h, dòng 278–282 (chỉ để xem, không compile)

  bool PlusJacobian(const double* x_ptr, double* jacobian_ptr) const override {
    Eigen::Map<MatrixJacobian> jacobian(jacobian_ptr, size_, size_);
    jacobian.setIdentity();
    return true;
  }

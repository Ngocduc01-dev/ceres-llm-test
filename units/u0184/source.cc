// u0184 – ceres::EuclideanManifold::MinusJacobian
// Trích từ include/ceres/manifold.h, dòng 302–306 (chỉ để xem, không compile)

  bool MinusJacobian(const double* x_ptr, double* jacobian_ptr) const override {
    Eigen::Map<MatrixJacobian> jacobian(jacobian_ptr, size_, size_);
    jacobian.setIdentity();
    return true;
  }

// u0182 – ceres::EuclideanManifold::RightMultiplyByPlusJacobian
// Trích từ include/ceres/manifold.h, dòng 284–290 (chỉ để xem, không compile)

  bool RightMultiplyByPlusJacobian(const double* x,
                                   const int num_rows,
                                   const double* ambient_matrix,
                                   double* tangent_matrix) const override {
    std::copy_n(ambient_matrix, num_rows * size_, tangent_matrix);
    return true;
  }

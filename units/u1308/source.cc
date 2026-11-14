// u1308 – ceres::internal::(anonymous)::BlockRandomAccessDiagonalMatrixAdapter::RightMultiplyAndAccumulate
// Trích từ internal/ceres/schur_complement_solver.cc, dòng 82–84 (chỉ để xem, không compile)

  void RightMultiplyAndAccumulate(const Vector& x, Vector& y) final {
    m_.RightMultiplyAndAccumulate(x.data(), y.data());
  }

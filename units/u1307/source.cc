// u1307 – ceres::internal::(anonymous)::BlockRandomAccessSparseMatrixAdapter::RightMultiplyAndAccumulate
// Trích từ internal/ceres/schur_complement_solver.cc, dòng 66–68 (chỉ để xem, không compile)

  void RightMultiplyAndAccumulate(const Vector& x, Vector& y) final {
    m_.SymmetricRightMultiplyAndAccumulate(x.data(), y.data());
  }

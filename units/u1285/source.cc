// u1285 – ceres::internal::CgnrLinearOperator::RightMultiplyAndAccumulate
// Trích từ internal/ceres/cgnr_solver.cc, dòng 97–113 (chỉ để xem, không compile)

  void RightMultiplyAndAccumulate(const Vector& x, Vector& y) final {
    // z = Ax
    // y = y + Atz
    z_.setZero();
    A_.RightMultiplyAndAccumulate(x, z_, context_, num_threads_);
    A_.LeftMultiplyAndAccumulate(z_, y, context_, num_threads_);

    // y = y + DtDx
    if (D_ != nullptr) {
      int n = A_.num_cols();
      ParallelAssign(
          context_,
          num_threads_,
          y,
          y.array() + ConstVectorRef(D_, n).array().square() * x.array());
    }
  }

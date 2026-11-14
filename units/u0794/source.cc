// u0794 – ceres::internal::SchurComplementSolver::set_lhs
// Trích từ internal/ceres/schur_complement_solver.h, dòng 128–130 (chỉ để xem, không compile)

  void set_lhs(std::unique_ptr<BlockRandomAccessMatrix> lhs) {
    lhs_ = std::move(lhs);
  }

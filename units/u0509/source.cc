// u0509 – ceres::internal::SparseSchurComplementSolver::~SparseSchurComplementSolver
// Trích từ internal/ceres/schur_complement_solver.cc, dòng 212–219 (chỉ để xem, không compile)

SparseSchurComplementSolver::~SparseSchurComplementSolver() {
  for (int i = 0; i < 4; ++i) {
    if (scratch_[i]) {
      delete scratch_[i];
      scratch_[i] = nullptr;
    }
  }
}

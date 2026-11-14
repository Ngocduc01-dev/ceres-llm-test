// u0503 – ceres::internal::CgnrSolver::~CgnrSolver
// Trích từ internal/ceres/cgnr_solver.cc, dòng 136–143 (chỉ để xem, không compile)

CgnrSolver::~CgnrSolver() {
  for (int i = 0; i < 4; ++i) {
    if (scratch_[i]) {
      delete scratch_[i];
      scratch_[i] = nullptr;
    }
  }
}

// u1351 – ceres::internal::SparseSchurComplementSolver::SparseSchurComplementSolver
// Trích từ internal/ceres/schur_complement_solver.cc, dòng 204–210 (chỉ để xem, không compile)

SparseSchurComplementSolver::SparseSchurComplementSolver(
    const LinearSolver::Options& options)
    : SchurComplementSolver(options) {
  if (options.type != ITERATIVE_SCHUR) {
    sparse_cholesky_ = SparseCholesky::Create(options);
  }
}

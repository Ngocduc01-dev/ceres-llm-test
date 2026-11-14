// u0939 – ceres::internal::SchurComplementSolver::SchurComplementSolver
// Trích từ internal/ceres/schur_complement_solver.cc, dòng 92–98 (chỉ để xem, không compile)

SchurComplementSolver::SchurComplementSolver(
    const LinearSolver::Options& options)
    : options_(options) {
  CHECK_GT(options.elimination_groups.size(), 1);
  CHECK_GT(options.elimination_groups[0], 0);
  CHECK(options.context != nullptr);
}

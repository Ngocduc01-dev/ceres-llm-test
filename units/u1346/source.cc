// u1346 – ceres::internal::SparseNormalCholeskySolver::SparseNormalCholeskySolver
// Trích từ internal/ceres/sparse_normal_cholesky_solver.cc, dòng 50–54 (chỉ để xem, không compile)

SparseNormalCholeskySolver::SparseNormalCholeskySolver(
    const LinearSolver::Options& options)
    : options_(options) {
  sparse_cholesky_ = SparseCholesky::Create(options);
}

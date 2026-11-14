// u1448 – ceres::internal::DenseNormalCholeskySolver::SolveImpl
// Trích từ internal/ceres/dense_normal_cholesky_solver.cc, dòng 49–87 (chỉ để xem, không compile)

LinearSolver::Summary DenseNormalCholeskySolver::SolveImpl(
    DenseSparseMatrix* A,
    const double* b,
    const LinearSolver::PerSolveOptions& per_solve_options,
    double* x) {
  EventLogger event_logger("DenseNormalCholeskySolver::Solve");

  const int num_rows = A->num_rows();
  const int num_cols = A->num_cols();

  Matrix lhs(num_cols, num_cols);
  lhs.setZero();

  event_logger.AddEvent("Setup");

  //   lhs += A'A
  //
  // Using rankUpdate instead of GEMM, exposes the fact that its the
  // same matrix being multiplied with itself and that the product is
  // symmetric.
  lhs.selfadjointView<Eigen::Upper>().rankUpdate(A->matrix().transpose());

  //   rhs = A'b
  Vector rhs = A->matrix().transpose() * ConstVectorRef(b, num_rows);

  if (per_solve_options.D != nullptr) {
    ConstVectorRef D(per_solve_options.D, num_cols);
    lhs += D.array().square().matrix().asDiagonal();
  }
  event_logger.AddEvent("Product");

  LinearSolver::Summary summary;
  summary.num_iterations = 1;
  summary.termination_type = cholesky_->FactorAndSolve(
      num_cols, lhs.data(), rhs.data(), x, &summary.message);
  event_logger.AddEvent("FactorAndSolve");

  return summary;
}

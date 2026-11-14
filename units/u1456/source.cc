// u1456 – ceres::internal::DenseQRSolver::SolveImpl
// Trích từ internal/ceres/dense_qr_solver.cc, dòng 48–81 (chỉ để xem, không compile)

LinearSolver::Summary DenseQRSolver::SolveImpl(
    DenseSparseMatrix* A,
    const double* b,
    const LinearSolver::PerSolveOptions& per_solve_options,
    double* x) {
  EventLogger event_logger("DenseQRSolver::Solve");

  const int num_rows = A->num_rows();
  const int num_cols = A->num_cols();
  const int num_augmented_rows =
      num_rows + ((per_solve_options.D != nullptr) ? num_cols : 0);

  if (lhs_.rows() != num_augmented_rows || lhs_.cols() != num_cols) {
    lhs_.resize(num_augmented_rows, num_cols);
    rhs_.resize(num_augmented_rows);
  }

  lhs_.topRows(num_rows) = A->matrix();
  rhs_.head(num_rows) = ConstVectorRef(b, num_rows);

  if (num_rows != num_augmented_rows) {
    lhs_.bottomRows(num_cols) =
        ConstVectorRef(per_solve_options.D, num_cols).asDiagonal();
    rhs_.tail(num_cols).setZero();
  }

  LinearSolver::Summary summary;
  summary.termination_type = dense_qr_->FactorAndSolve(
      lhs_.rows(), lhs_.cols(), lhs_.data(), rhs_.data(), x, &summary.message);
  summary.num_iterations = 1;
  event_logger.AddEvent("Solve");

  return summary;
}

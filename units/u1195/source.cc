// u1195 – ceres::internal::LinearSolver::LinearSolverForZeroEBlocks
// Trích từ internal/ceres/linear_solver.cc, dòng 50–72 (chỉ để xem, không compile)

LinearSolverType LinearSolver::LinearSolverForZeroEBlocks(
    LinearSolverType linear_solver_type) {
  if (!IsSchurType(linear_solver_type)) {
    return linear_solver_type;
  }

  if (linear_solver_type == SPARSE_SCHUR) {
    return SPARSE_NORMAL_CHOLESKY;
  }

  if (linear_solver_type == DENSE_SCHUR) {
    // TODO(sameeragarwal): This is probably not a great choice.
    // Ideally, we should have a DENSE_NORMAL_CHOLESKY, that can take
    // a BlockSparseMatrix as input.
    return DENSE_QR;
  }

  if (linear_solver_type == ITERATIVE_SCHUR) {
    return CGNR;
  }

  return linear_solver_type;
}

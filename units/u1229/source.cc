// u1229 – ceres::internal::DenseSchurComplementSolver::SolveReducedLinearSystem
// Trích từ internal/ceres/schur_complement_solver.cc, dòng 181–202 (chỉ để xem, không compile)

LinearSolver::Summary DenseSchurComplementSolver::SolveReducedLinearSystem(
    const LinearSolver::PerSolveOptions& /*per_solve_options*/,
    double* solution) {
  LinearSolver::Summary summary;
  summary.num_iterations = 0;
  summary.termination_type = LinearSolverTerminationType::SUCCESS;
  summary.message = "Success.";

  auto* m = down_cast<BlockRandomAccessDenseMatrix*>(mutable_lhs());
  const int num_rows = m->num_rows();

  // The case where there are no f blocks, and the system is block
  // diagonal.
  if (num_rows == 0) {
    return summary;
  }

  summary.num_iterations = 1;
  summary.termination_type = cholesky_->FactorAndSolve(
      num_rows, m->mutable_values(), rhs().data(), solution, &summary.message);
  return summary;
}

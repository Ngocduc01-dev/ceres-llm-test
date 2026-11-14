// u0959 – ceres::internal::DynamicSparseNormalCholeskySolver::SolveImplUsingSuiteSparse
// Trích từ internal/ceres/dynamic_sparse_normal_cholesky_solver.cc, dòng 174–232 (chỉ để xem, không compile)

LinearSolver::Summary
DynamicSparseNormalCholeskySolver::SolveImplUsingSuiteSparse(
    CompressedRowSparseMatrix* A, double* rhs_and_solution) {
#ifdef CERES_NO_SUITESPARSE
  (void)A;
  (void)rhs_and_solution;

  LinearSolver::Summary summary;
  summary.num_iterations = 0;
  summary.termination_type = LinearSolverTerminationType::FATAL_ERROR;
  summary.message =
      "SPARSE_NORMAL_CHOLESKY cannot be used with SUITE_SPARSE "
      "because Ceres was not built with support for SuiteSparse. "
      "This requires enabling building with -DSUITESPARSE=ON.";
  return summary;

#else

  EventLogger event_logger(
      "DynamicSparseNormalCholeskySolver::SuiteSparse::Solve");
  LinearSolver::Summary summary;
  summary.termination_type = LinearSolverTerminationType::SUCCESS;
  summary.num_iterations = 1;
  summary.message = "Success.";

  SuiteSparse ss;
  const int num_cols = A->num_cols();
  cholmod_sparse lhs = ss.CreateSparseMatrixTransposeView(A);
  event_logger.AddEvent("Setup");
  cholmod_factor* factor =
      ss.AnalyzeCholesky(&lhs, options_.ordering_type, &summary.message);
  event_logger.AddEvent("Analysis");

  if (factor == nullptr) {
    summary.termination_type = LinearSolverTerminationType::FATAL_ERROR;
    return summary;
  }

  summary.termination_type = ss.Cholesky(&lhs, factor, &summary.message);
  if (summary.termination_type == LinearSolverTerminationType::SUCCESS) {
    cholmod_dense cholmod_rhs =
        ss.CreateDenseVectorView(rhs_and_solution, num_cols);
    cholmod_dense* solution = ss.Solve(factor, &cholmod_rhs, &summary.message);
    event_logger.AddEvent("Solve");
    if (solution != nullptr) {
      memcpy(
          rhs_and_solution, solution->x, num_cols * sizeof(*rhs_and_solution));
      ss.Free(solution);
    } else {
      summary.termination_type = LinearSolverTerminationType::FAILURE;
    }
  }

  ss.Free(factor);
  event_logger.AddEvent("Teardown");
  return summary;

#endif
}

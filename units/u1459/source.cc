// u1459 – ceres::internal::DynamicSparseNormalCholeskySolver::SolveImplUsingEigen
// Trích từ internal/ceres/dynamic_sparse_normal_cholesky_solver.cc, dòng 105–172 (chỉ để xem, không compile)

LinearSolver::Summary DynamicSparseNormalCholeskySolver::SolveImplUsingEigen(
    CompressedRowSparseMatrix* A, double* rhs_and_solution) {
#ifndef CERES_USE_EIGEN_SPARSE

  LinearSolver::Summary summary;
  summary.num_iterations = 0;
  summary.termination_type = LinearSolverTerminationType::FATAL_ERROR;
  summary.message =
      "SPARSE_NORMAL_CHOLESKY cannot be used with EIGEN_SPARSE "
      "because Ceres was not built with support for "
      "Eigen's SimplicialLDLT decomposition. "
      "This requires enabling building with -DEIGENSPARSE=ON.";
  return summary;

#else

  EventLogger event_logger("DynamicSparseNormalCholeskySolver::Eigen::Solve");

  Eigen::Map<Eigen::SparseMatrix<double, Eigen::RowMajor>> a(
      A->num_rows(),
      A->num_cols(),
      A->num_nonzeros(),
      A->mutable_rows(),
      A->mutable_cols(),
      A->mutable_values());

  Eigen::SparseMatrix<double> lhs = a.transpose() * a;
  Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>> solver;

  LinearSolver::Summary summary;
  summary.num_iterations = 1;
  summary.termination_type = LinearSolverTerminationType::SUCCESS;
  summary.message = "Success.";

  solver.analyzePattern(lhs);
  if (VLOG_IS_ON(2)) {
    std::stringstream ss;
    solver.dumpMemory(ss);
    VLOG(2) << "Symbolic Analysis\n" << ss.str();
  }

  event_logger.AddEvent("Analyze");
  if (solver.info() != Eigen::Success) {
    summary.termination_type = LinearSolverTerminationType::FATAL_ERROR;
    summary.message = "Eigen failure. Unable to find symbolic factorization.";
    return summary;
  }

  solver.factorize(lhs);
  event_logger.AddEvent("Factorize");
  if (solver.info() != Eigen::Success) {
    summary.termination_type = LinearSolverTerminationType::FAILURE;
    summary.message = "Eigen failure. Unable to find numeric factorization.";
    return summary;
  }

  const Vector rhs = VectorRef(rhs_and_solution, lhs.cols());
  VectorRef(rhs_and_solution, lhs.cols()) = solver.solve(rhs);
  event_logger.AddEvent("Solve");
  if (solver.info() != Eigen::Success) {
    summary.termination_type = LinearSolverTerminationType::FAILURE;
    summary.message = "Eigen failure. Unable to do triangular solve.";
    return summary;
  }

  return summary;
#endif  // CERES_USE_EIGEN_SPARSE
}

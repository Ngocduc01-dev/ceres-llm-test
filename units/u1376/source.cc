// u1376 – ceres::internal::(anonymous)::AlternateLinearSolverAndPreconditionerForSchurTypeLinearSolver
// Trích từ internal/ceres/trust_region_preprocessor.cc, dòng 75–107 (chỉ để xem, không compile)

void AlternateLinearSolverAndPreconditionerForSchurTypeLinearSolver(
    Solver::Options* options) {
  if (!IsSchurType(options->linear_solver_type)) {
    return;
  }

  const LinearSolverType linear_solver_type_given = options->linear_solver_type;
  const PreconditionerType preconditioner_type_given =
      options->preconditioner_type;
  options->linear_solver_type =
      LinearSolver::LinearSolverForZeroEBlocks(linear_solver_type_given);

  std::string message;
  if (linear_solver_type_given == ITERATIVE_SCHUR) {
    options->preconditioner_type =
        Preconditioner::PreconditionerForZeroEBlocks(preconditioner_type_given);

    message =
        StringPrintf("No E blocks. Switching from %s(%s) to %s(%s).",
                     LinearSolverTypeToString(linear_solver_type_given),
                     PreconditionerTypeToString(preconditioner_type_given),
                     LinearSolverTypeToString(options->linear_solver_type),
                     PreconditionerTypeToString(options->preconditioner_type));
  } else {
    message =
        StringPrintf("No E blocks. Switching from %s to %s.",
                     LinearSolverTypeToString(linear_solver_type_given),
                     LinearSolverTypeToString(options->linear_solver_type));
  }
  if (options->logging_type != SILENT) {
    VLOG(1) << message;
  }
}

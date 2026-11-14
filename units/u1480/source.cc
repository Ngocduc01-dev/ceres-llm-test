// u1480 – ceres::(anonymous)::OptionsAreValidForLinearSolver
// Trích từ internal/ceres/solver.cc, dòng 363–387 (chỉ để xem, không compile)

bool OptionsAreValidForLinearSolver(const Solver::Options& options,
                                    std::string* error) {
  switch (options.linear_solver_type) {
    case DENSE_NORMAL_CHOLESKY:
      return OptionsAreValidForDenseNormalCholesky(options, error);
    case DENSE_QR:
      return OptionsAreValidForDenseQr(options, error);
    case SPARSE_NORMAL_CHOLESKY:
      return OptionsAreValidForSparseNormalCholesky(options, error);
    case DENSE_SCHUR:
      return OptionsAreValidForDenseSchur(options, error);
    case SPARSE_SCHUR:
      return OptionsAreValidForSparseSchur(options, error);
    case ITERATIVE_SCHUR:
      return OptionsAreValidForIterativeSchur(options, error);
    case CGNR:
      return OptionsAreValidForCgnr(options, error);
    default:
      LOG(FATAL) << "Congratulations you have found a bug. Please report "
                    "this to the "
                    "Ceres Solver developers. Unknown linear solver type: "
                 << LinearSolverTypeToString(options.linear_solver_type);
  }
  return false;
}

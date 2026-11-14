// u1420 – ceres::(anonymous)::OptionsAreValidForIterativeSchur
// Trích từ internal/ceres/solver.cc, dòng 253–305 (chỉ để xem, không compile)

bool OptionsAreValidForIterativeSchur(const Solver::Options& options,
                                      std::string* error) {
  CHECK_EQ(options.linear_solver_type, ITERATIVE_SCHUR);
  if (options.dynamic_sparsity) {
    *error = "Dynamic sparsity is only supported with SPARSE_NORMAL_CHOLESKY.";
    return false;
  }

  if (options.use_explicit_schur_complement) {
    if (options.preconditioner_type != SCHUR_JACOBI) {
      *error =
          "use_explicit_schur_complement only supports "
          "SCHUR_JACOBI as the preconditioner.";
      return false;
    }
    if (options.use_spse_initialization) {
      *error =
          "use_explicit_schur_complement does not support "
          "use_spse_initialization.";
      return false;
    }
  }

  if (options.use_spse_initialization ||
      options.preconditioner_type == SCHUR_POWER_SERIES_EXPANSION) {
    OPTION_GE(max_num_spse_iterations, 1)
    OPTION_GE(spse_tolerance, 0.0)
  }

  if (options.use_mixed_precision_solves) {
    *error = "Can't use use_mixed_precision_solves with ITERATIVE_SCHUR";
    return false;
  }

  if (options.dynamic_sparsity) {
    *error = "Dynamic sparsity is only supported with SPARSE_NORMAL_CHOLESKY.";
    return false;
  }

  if (options.preconditioner_type == SUBSET) {
    *error = "Can't use SUBSET preconditioner with ITERATIVE_SCHUR";
    return false;
  }

  // CLUSTER_JACOBI and CLUSTER_TRIDIAGONAL require sparse Cholesky
  // factorization.
  if (options.preconditioner_type == CLUSTER_JACOBI ||
      options.preconditioner_type == CLUSTER_TRIDIAGONAL) {
    return OptionsAreValidForSparseCholeskyBasedSolver(options, error);
  }

  return true;
}

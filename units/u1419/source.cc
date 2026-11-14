// u1419 – ceres::(anonymous)::OptionsAreValidForCgnr
// Trích từ internal/ceres/solver.cc, dòng 307–361 (chỉ để xem, không compile)

bool OptionsAreValidForCgnr(const Solver::Options& options,
                            std::string* error) {
  CHECK_EQ(options.linear_solver_type, CGNR);

  if (options.preconditioner_type != IDENTITY &&
      options.preconditioner_type != JACOBI &&
      options.preconditioner_type != SUBSET) {
    *error =
        StringPrintf("Can't use CGNR with preconditioner_type = %s.",
                     PreconditionerTypeToString(options.preconditioner_type));
    return false;
  }

  if (options.use_mixed_precision_solves) {
    *error = "use_mixed_precision_solves cannot be used with CGNR";
    return false;
  }

  if (options.dynamic_sparsity) {
    *error = "Dynamic sparsity is only supported with SPARSE_NORMAL_CHOLESKY.";
    return false;
  }

  if (options.preconditioner_type == SUBSET) {
    if (options.sparse_linear_algebra_library_type == CUDA_SPARSE) {
      *error =
          "Can't use CGNR with preconditioner_type = SUBSET when "
          "sparse_linear_algebra_library_type = CUDA_SPARSE.";
      return false;
    }

    if (options.residual_blocks_for_subset_preconditioner.empty()) {
      *error =
          "When using SUBSET preconditioner, "
          "residual_blocks_for_subset_preconditioner cannot be empty";
      return false;
    }

    // SUBSET preconditioner requires sparse Cholesky factorization.
    if (!OptionsAreValidForSparseCholeskyBasedSolver(options, error)) {
      return false;
    }
  }

  // Check options for CGNR with CUDA_SPARSE.
  if (options.sparse_linear_algebra_library_type == CUDA_SPARSE) {
    if (!IsSparseLinearAlgebraLibraryTypeAvailable(CUDA_SPARSE)) {
      *error =
          "Can't use CGNR with sparse_linear_algebra_library_type = "
          "CUDA_SPARSE because support was not enabled when Ceres was built.";
      return false;
    }
  }
  return true;
}

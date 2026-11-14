// u1316 – ceres::(anonymous)::OptionsAreValidForSparseCholeskyBasedSolver
// Trích từ internal/ceres/solver.cc, dòng 141–197 (chỉ để xem, không compile)

bool OptionsAreValidForSparseCholeskyBasedSolver(const Solver::Options& options,
                                                 std::string* error) {
  const char* library_name = SparseLinearAlgebraLibraryTypeToString(
      options.sparse_linear_algebra_library_type);
  // Sparse factorization based solvers and some preconditioners require a
  // sparse Cholesky factorization.
  const char* solver_name =
      IsIterativeSolver(options.linear_solver_type)
          ? PreconditionerTypeToString(options.preconditioner_type)
          : LinearSolverTypeToString(options.linear_solver_type);

  constexpr char kNoSparseFormat[] =
      "Can't use %s with sparse_linear_algebra_library_type = %s.";
  constexpr char kNoLibraryFormat[] =
      "Can't use %s sparse_linear_algebra_library_type = %s, because support "
      "was not enabled when Ceres Solver was built.";
  constexpr char kNoNesdisFormat[] =
      "NESDIS is not available with sparse_linear_algebra_library_type = %s.";
  constexpr char kMixedFormat[] =
      "use_mixed_precision_solves with %s is not supported with "
      "sparse_linear_algebra_library_type = %s";
  constexpr char kDynamicSparsityFormat[] =
      "dynamic sparsity is not supported with "
      "sparse_linear_algebra_library_type = %s";

  if (options.sparse_linear_algebra_library_type == NO_SPARSE) {
    *error = StringPrintf(kNoSparseFormat, solver_name, library_name);
    return false;
  }

  if (!IsSparseLinearAlgebraLibraryTypeAvailable(
          options.sparse_linear_algebra_library_type)) {
    *error = StringPrintf(kNoLibraryFormat, solver_name, library_name);
    return false;
  }

  if (options.linear_solver_ordering_type == ceres::NESDIS &&
      !IsNestedDissectionAvailable(
          options.sparse_linear_algebra_library_type)) {
    *error = StringPrintf(kNoNesdisFormat, library_name);
    return false;
  }

  if (options.use_mixed_precision_solves &&
      options.sparse_linear_algebra_library_type == SUITE_SPARSE) {
    *error = StringPrintf(kMixedFormat, solver_name, library_name);
    return false;
  }

  if (options.dynamic_sparsity &&
      options.sparse_linear_algebra_library_type == ACCELERATE_SPARSE) {
    *error = StringPrintf(kDynamicSparsityFormat, library_name);
    return false;
  }

  return true;
}

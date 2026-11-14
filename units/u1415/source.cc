// u1415 – ceres::(anonymous)::OptionsAreValidForSparseSchur
// Trích từ internal/ceres/solver.cc, dòng 243–251 (chỉ để xem, không compile)

bool OptionsAreValidForSparseSchur(const Solver::Options& options,
                                   std::string* error) {
  CHECK_EQ(options.linear_solver_type, SPARSE_SCHUR);
  if (options.dynamic_sparsity) {
    *error = "Dynamic sparsity is only supported with SPARSE_NORMAL_CHOLESKY.";
    return false;
  }
  return OptionsAreValidForSparseCholeskyBasedSolver(options, error);
}

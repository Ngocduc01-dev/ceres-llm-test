// u1417 – ceres::(anonymous)::OptionsAreValidForDenseSchur
// Trích từ internal/ceres/solver.cc, dòng 227–241 (chỉ để xem, không compile)

bool OptionsAreValidForDenseSchur(const Solver::Options& options,
                                  std::string* error) {
  CHECK_EQ(options.linear_solver_type, DENSE_SCHUR);

  if (options.dynamic_sparsity) {
    *error = "dynamic sparsity is only supported with SPARSE_NORMAL_CHOLESKY";
    return false;
  }

  if (!OptionsAreValidForDenseSolver(options, error)) {
    return false;
  }

  return true;
}

// u1416 – ceres::(anonymous)::OptionsAreValidForDenseQr
// Trích từ internal/ceres/solver.cc, dòng 205–219 (chỉ để xem, không compile)

bool OptionsAreValidForDenseQr(const Solver::Options& options,
                               std::string* error) {
  CHECK_EQ(options.linear_solver_type, DENSE_QR);

  if (!OptionsAreValidForDenseSolver(options, error)) {
    return false;
  }

  if (options.use_mixed_precision_solves) {
    *error = "Can't use use_mixed_precision_solves with DENSE_QR.";
    return false;
  }

  return true;
}

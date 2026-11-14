// u1310 – ceres::(anonymous)::OptionsAreValidForDenseSolver
// Trích từ internal/ceres/solver.cc, dòng 123–139 (chỉ để xem, không compile)

bool OptionsAreValidForDenseSolver(const Solver::Options& options,
                                   std::string* error) {
  const char* library_name = DenseLinearAlgebraLibraryTypeToString(
      options.dense_linear_algebra_library_type);
  const char* solver_name =
      LinearSolverTypeToString(options.linear_solver_type);
  constexpr char kFormat[] =
      "Can't use %s with dense_linear_algebra_library_type = %s "
      "because support not enabled when Ceres was built.";

  if (!IsDenseLinearAlgebraLibraryTypeAvailable(
          options.dense_linear_algebra_library_type)) {
    *error = StringPrintf(kFormat, solver_name, library_name);
    return false;
  }
  return true;
}

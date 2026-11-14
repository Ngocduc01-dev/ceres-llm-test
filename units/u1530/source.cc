// u1530 – ceres::GradientProblemSolver::Options::IsValid
// Trích từ internal/ceres/gradient_problem_solver.cc, dòng 90–94 (chỉ để xem, không compile)

bool GradientProblemSolver::Options::IsValid(std::string* error) const {
  const Solver::Options solver_options =
      GradientProblemSolverOptionsToSolverOptions(*this);
  return solver_options.IsValid(error);
}

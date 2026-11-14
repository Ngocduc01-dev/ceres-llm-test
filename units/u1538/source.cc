// u1538 – ceres::Solve
// Trích từ internal/ceres/gradient_problem_solver.cc, dòng 290–296 (chỉ để xem, không compile)

void Solve(const GradientProblemSolver::Options& options,
           const GradientProblem& problem,
           double* parameters,
           GradientProblemSolver::Summary* summary) {
  GradientProblemSolver solver;
  solver.Solve(options, problem, parameters, summary);
}

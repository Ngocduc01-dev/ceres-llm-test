// u0308 – ceres::GradientProblemSolver::Summary::IsSolutionUsable
// Trích từ internal/ceres/gradient_problem_solver.cc, dòng 203–205 (chỉ để xem, không compile)

bool GradientProblemSolver::Summary::IsSolutionUsable() const {
  return internal::IsSolutionUsable(*this);
}

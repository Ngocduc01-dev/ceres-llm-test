// u1245 – ceres::GradientProblemSolver::Summary::BriefReport
// Trích từ internal/ceres/gradient_problem_solver.cc, dòng 207–218 (chỉ để xem, không compile)

std::string GradientProblemSolver::Summary::BriefReport() const {
  return StringPrintf(
      "Ceres GradientProblemSolver Report: "
      "Iterations: %d, "
      "Initial cost: %e, "
      "Final cost: %e, "
      "Termination: %s",
      static_cast<int>(iterations.size()),
      initial_cost,
      final_cost,
      TerminationTypeToString(termination_type));
}

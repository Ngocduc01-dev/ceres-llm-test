// u1256 – ceres::Solver::Summary::BriefReport
// Trích từ internal/ceres/solver.cc, dòng 839–850 (chỉ để xem, không compile)

std::string Solver::Summary::BriefReport() const {
  return StringPrintf(
      "Ceres Solver Report: "
      "Iterations: %d, "
      "Initial cost: %e, "
      "Final cost: %e, "
      "Termination: %s",
      num_successful_steps + num_unsuccessful_steps,
      initial_cost,
      final_cost,
      TerminationTypeToString(termination_type));
}

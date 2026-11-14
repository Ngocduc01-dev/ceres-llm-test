// u1399 – ceres::internal::CoordinateDescentMinimizer::IsOrderingValid
// Trích từ internal/ceres/coordinate_descent_minimizer.cc, dòng 239–259 (chỉ để xem, không compile)

bool CoordinateDescentMinimizer::IsOrderingValid(
    const Program& program,
    const ParameterBlockOrdering& ordering,
    std::string* message) {
  // TODO(sameeragarwal): Investigate if this should be an ordered or an
  // unordered group.
  const std::map<int, std::set<double*>>& group_to_elements =
      ordering.group_to_elements();

  // Verify that each group is an independent set
  for (const auto& g_t_e : group_to_elements) {
    if (!program.IsParameterBlockSetIndependent(g_t_e.second)) {
      *message = StringPrintf(
          "The user-provided parameter_blocks_for_inner_iterations does not "
          "form an independent set. Group Id: %d",
          g_t_e.first);
      return false;
    }
  }
  return true;
}

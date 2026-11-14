// u1297 – ceres::internal::ApplyOrdering
// Trích từ internal/ceres/reorder_program.cc, dòng 214–252 (chỉ để xem, không compile)

bool ApplyOrdering(const ProblemImpl::ParameterMap& parameter_map,
                   const ParameterBlockOrdering& ordering,
                   Program* program,
                   std::string* error) {
  const int num_parameter_blocks = program->NumParameterBlocks();
  if (ordering.NumElements() != num_parameter_blocks) {
    *error = StringPrintf(
        "User specified ordering does not have the same "
        "number of parameters as the problem. The problem"
        "has %d blocks while the ordering has %d blocks.",
        num_parameter_blocks,
        ordering.NumElements());
    return false;
  }

  std::vector<ParameterBlock*>* parameter_blocks =
      program->mutable_parameter_blocks();
  parameter_blocks->clear();

  // TODO(sameeragarwal): Investigate whether this should be a set or an
  // unordered_set.
  const std::map<int, std::set<double*>>& groups = ordering.group_to_elements();
  for (const auto& p : groups) {
    const std::set<double*>& group = p.second;
    for (double* parameter_block_ptr : group) {
      auto it = parameter_map.find(parameter_block_ptr);
      if (it == parameter_map.end()) {
        *error = StringPrintf(
            "User specified ordering contains a pointer "
            "to a double that is not a parameter block in "
            "the problem. The invalid double is in group: %d",
            p.first);
        return false;
      }
      parameter_blocks->push_back(it->second);
    }
  }
  return true;
}

// u1405 – ceres::internal::ComputeStableSchurOrdering
// Trích từ internal/ceres/parameter_block_ordering.cc, dòng 50–80 (chỉ để xem, không compile)

int ComputeStableSchurOrdering(const Program& program,
                               std::vector<ParameterBlock*>* ordering) {
  CHECK(ordering != nullptr);
  ordering->clear();
  EventLogger event_logger("ComputeStableSchurOrdering");
  auto graph = CreateHessianGraph(program);
  event_logger.AddEvent("CreateHessianGraph");

  const std::vector<ParameterBlock*>& parameter_blocks =
      program.parameter_blocks();
  const std::unordered_set<ParameterBlock*>& vertices = graph->vertices();
  for (auto* parameter_block : parameter_blocks) {
    if (vertices.count(parameter_block) > 0) {
      ordering->push_back(parameter_block);
    }
  }
  event_logger.AddEvent("Preordering");

  int independent_set_size = StableIndependentSetOrdering(*graph, ordering);
  event_logger.AddEvent("StableIndependentSet");

  // Add the excluded blocks to back of the ordering vector.
  for (auto* parameter_block : parameter_blocks) {
    if (parameter_block->IsConstant()) {
      ordering->push_back(parameter_block);
    }
  }
  event_logger.AddEvent("ConstantParameterBlocks");

  return independent_set_size;
}

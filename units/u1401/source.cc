// u1401 – ceres::internal::ComputeSchurOrdering
// Trích từ internal/ceres/parameter_block_ordering.cc, dòng 82–100 (chỉ để xem, không compile)

int ComputeSchurOrdering(const Program& program,
                         std::vector<ParameterBlock*>* ordering) {
  CHECK(ordering != nullptr);
  ordering->clear();

  auto graph = CreateHessianGraph(program);
  int independent_set_size = IndependentSetOrdering(*graph, ordering);
  const std::vector<ParameterBlock*>& parameter_blocks =
      program.parameter_blocks();

  // Add the excluded blocks to back of the ordering vector.
  for (auto* parameter_block : parameter_blocks) {
    if (parameter_block->IsConstant()) {
      ordering->push_back(parameter_block);
    }
  }

  return independent_set_size;
}

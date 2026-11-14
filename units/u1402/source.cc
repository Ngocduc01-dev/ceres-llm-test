// u1402 – ceres::internal::ComputeRecursiveIndependentSetOrdering
// Trích từ internal/ceres/parameter_block_ordering.cc, dòng 102–124 (chỉ để xem, không compile)

void ComputeRecursiveIndependentSetOrdering(const Program& program,
                                            ParameterBlockOrdering* ordering) {
  CHECK(ordering != nullptr);
  ordering->Clear();
  const std::vector<ParameterBlock*> parameter_blocks =
      program.parameter_blocks();
  auto graph = CreateHessianGraph(program);

  int num_covered = 0;
  int round = 0;
  while (num_covered < parameter_blocks.size()) {
    std::vector<ParameterBlock*> independent_set_ordering;
    const int independent_set_size =
        IndependentSetOrdering(*graph, &independent_set_ordering);
    for (int i = 0; i < independent_set_size; ++i) {
      ParameterBlock* parameter_block = independent_set_ordering[i];
      ordering->AddElementToGroup(parameter_block->mutable_user_state(), round);
      graph->RemoveVertex(parameter_block);
    }
    num_covered += independent_set_size;
    ++round;
  }
}

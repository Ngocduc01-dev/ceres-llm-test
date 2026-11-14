// u1303 – ceres::internal::CreateHessianGraph
// Trích từ internal/ceres/parameter_block_ordering.cc, dòng 126–160 (chỉ để xem, không compile)

std::unique_ptr<Graph<ParameterBlock*>> CreateHessianGraph(
    const Program& program) {
  auto graph = std::make_unique<Graph<ParameterBlock*>>();
  CHECK(graph != nullptr);
  const std::vector<ParameterBlock*>& parameter_blocks =
      program.parameter_blocks();
  for (auto* parameter_block : parameter_blocks) {
    if (!parameter_block->IsConstant()) {
      graph->AddVertex(parameter_block);
    }
  }

  const std::vector<ResidualBlock*>& residual_blocks =
      program.residual_blocks();
  for (auto* residual_block : residual_blocks) {
    const int num_parameter_blocks = residual_block->NumParameterBlocks();
    ParameterBlock* const* parameter_blocks =
        residual_block->parameter_blocks();
    for (int j = 0; j < num_parameter_blocks; ++j) {
      if (parameter_blocks[j]->IsConstant()) {
        continue;
      }

      for (int k = j + 1; k < num_parameter_blocks; ++k) {
        if (parameter_blocks[k]->IsConstant()) {
          continue;
        }

        graph->AddEdge(parameter_blocks[j], parameter_blocks[k]);
      }
    }
  }

  return graph;
}

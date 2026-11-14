// u1301 – ceres::internal::CoordinateDescentMinimizer::Init
// Trích từ internal/ceres/coordinate_descent_minimizer.cc, dòng 64–126 (chỉ để xem, không compile)

bool CoordinateDescentMinimizer::Init(
    const Program& program,
    const ProblemImpl::ParameterMap& parameter_map,
    const ParameterBlockOrdering& ordering,
    std::string* /*error*/) {
  parameter_blocks_.clear();
  independent_set_offsets_.clear();
  independent_set_offsets_.push_back(0);

  // Serialize the OrderedGroups into a vector of parameter block
  // offsets for parallel access.

  // TODO(sameeragarwal): Investigate if parameter_block_index should be an
  // ordered or an unordered container.
  std::map<ParameterBlock*, int> parameter_block_index;
  std::map<int, std::set<double*>> group_to_elements =
      ordering.group_to_elements();
  for (const auto& g_t_e : group_to_elements) {
    const auto& elements = g_t_e.second;
    for (double* parameter_block : elements) {
      parameter_blocks_.push_back(parameter_map.find(parameter_block)->second);
      parameter_block_index[parameter_blocks_.back()] =
          parameter_blocks_.size() - 1;
    }
    independent_set_offsets_.push_back(independent_set_offsets_.back() +
                                       elements.size());
  }

  // The ordering does not have to contain all parameter blocks, so
  // assign zero offsets/empty independent sets to these parameter
  // blocks.
  const std::vector<ParameterBlock*>& parameter_blocks =
      program.parameter_blocks();
  for (auto* parameter_block : parameter_blocks) {
    if (!ordering.IsMember(parameter_block->mutable_user_state())) {
      parameter_blocks_.push_back(parameter_block);
      independent_set_offsets_.push_back(independent_set_offsets_.back());
    }
  }

  // Compute the set of residual blocks that depend on each parameter
  // block.
  residual_blocks_.resize(parameter_block_index.size());
  const std::vector<ResidualBlock*>& residual_blocks =
      program.residual_blocks();
  for (auto* residual_block : residual_blocks) {
    const int num_parameter_blocks = residual_block->NumParameterBlocks();
    for (int j = 0; j < num_parameter_blocks; ++j) {
      ParameterBlock* parameter_block = residual_block->parameter_blocks()[j];
      const auto it = parameter_block_index.find(parameter_block);
      if (it != parameter_block_index.end()) {
        residual_blocks_[it->second].push_back(residual_block);
      }
    }
  }

  evaluator_options_.linear_solver_type = DENSE_QR;
  evaluator_options_.num_eliminate_blocks = 0;
  evaluator_options_.num_threads = 1;
  evaluator_options_.context = context_;

  return true;
}

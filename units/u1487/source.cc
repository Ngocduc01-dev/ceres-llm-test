// u1487 – ceres::internal::CoordinateDescentMinimizer::Minimize
// Trích từ internal/ceres/coordinate_descent_minimizer.cc, dòng 128–208 (chỉ để xem, không compile)

void CoordinateDescentMinimizer::Minimize(const Minimizer::Options& options,
                                          double* parameters,
                                          Solver::Summary* /*summary*/) {
  // Set the state and mark all parameter blocks constant.
  for (auto* parameter_block : parameter_blocks_) {
    parameter_block->SetState(parameters + parameter_block->state_offset());
    parameter_block->SetConstant();
  }

  std::vector<std::unique_ptr<LinearSolver>> linear_solvers(
      options.num_threads);

  LinearSolver::Options linear_solver_options;
  linear_solver_options.type = DENSE_QR;
  linear_solver_options.context = context_;

  for (int i = 0; i < options.num_threads; ++i) {
    linear_solvers[i] = LinearSolver::Create(linear_solver_options);
  }

  for (int i = 0; i < independent_set_offsets_.size() - 1; ++i) {
    const int num_problems =
        independent_set_offsets_[i + 1] - independent_set_offsets_[i];
    // Avoid parallelization overhead call if the set is empty.
    if (num_problems == 0) {
      continue;
    }

    const int num_inner_iteration_threads =
        std::min(options.num_threads, num_problems);
    evaluator_options_.num_threads =
        std::max(1, options.num_threads / num_inner_iteration_threads);

    // The parameter blocks in each independent set can be optimized
    // in parallel, since they do not co-occur in any residual block.
    ParallelFor(
        context_,
        independent_set_offsets_[i],
        independent_set_offsets_[i + 1],
        num_inner_iteration_threads,
        [&](int thread_id, int j) {
          ParameterBlock* parameter_block = parameter_blocks_[j];
          const int old_index = parameter_block->index();
          const int old_delta_offset = parameter_block->delta_offset();
          const int old_state_offset = parameter_block->state_offset();
          parameter_block->SetVarying();
          parameter_block->set_index(0);
          parameter_block->set_delta_offset(0);
          parameter_block->set_state_offset(0);

          Program inner_program;
          inner_program.mutable_parameter_blocks()->push_back(parameter_block);
          *inner_program.mutable_residual_blocks() = residual_blocks_[j];

          // TODO(sameeragarwal): Better error handling. Right now we
          // assume that this is not going to lead to problems of any
          // sort. Basically we should be checking for numerical failure
          // of some sort.
          //
          // On the other hand, if the optimization is a failure, that in
          // some ways is fine, since it won't change the parameters and
          // we are fine.
          Solver::Summary inner_summary;
          Solve(&inner_program,
                linear_solvers[thread_id].get(),
                parameters + old_state_offset,
                &inner_summary);

          parameter_block->set_index(old_index);
          parameter_block->set_delta_offset(old_delta_offset);
          parameter_block->set_state_offset(old_state_offset);
          parameter_block->SetState(parameters +
                                    parameter_block->state_offset());
          parameter_block->SetConstant();
        });
  }

  for (auto* parameter_block : parameter_blocks_) {
    parameter_block->SetVarying();
  }
}

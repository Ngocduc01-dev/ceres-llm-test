// u1230 – ceres::internal::(anonymous)::SetupEvaluator
// Trích từ internal/ceres/trust_region_preprocessor.cc, dòng 260–283 (chỉ để xem, không compile)

bool SetupEvaluator(PreprocessedProblem* pp) {
  const Solver::Options& options = pp->options;
  pp->evaluator_options = Evaluator::Options();
  pp->evaluator_options.linear_solver_type = options.linear_solver_type;
  pp->evaluator_options.sparse_linear_algebra_library_type =
      options.sparse_linear_algebra_library_type;
  pp->evaluator_options.num_eliminate_blocks = 0;
  if (IsSchurType(options.linear_solver_type)) {
    pp->evaluator_options.num_eliminate_blocks =
        options.linear_solver_ordering->group_to_elements()
            .begin()
            ->second.size();
  }

  pp->evaluator_options.num_threads = options.num_threads;
  pp->evaluator_options.dynamic_sparsity = options.dynamic_sparsity;
  pp->evaluator_options.context = pp->problem->context();
  pp->evaluator_options.evaluation_callback =
      pp->reduced_program->mutable_evaluation_callback();
  pp->evaluator = Evaluator::Create(
      pp->evaluator_options, pp->reduced_program.get(), &pp->error);

  return (pp->evaluator != nullptr);
}

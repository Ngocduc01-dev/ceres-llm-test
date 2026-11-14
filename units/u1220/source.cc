// u1220 – ceres::internal::(anonymous)::SetupEvaluator
// Trích từ internal/ceres/line_search_preprocessor.cc, dòng 55–68 (chỉ để xem, không compile)

bool SetupEvaluator(PreprocessedProblem* pp) {
  pp->evaluator_options = Evaluator::Options();
  // This ensures that we get a Block Jacobian Evaluator without any
  // requirement on orderings.
  pp->evaluator_options.linear_solver_type = CGNR;
  pp->evaluator_options.num_eliminate_blocks = 0;
  pp->evaluator_options.num_threads = pp->options.num_threads;
  pp->evaluator_options.context = pp->problem->context();
  pp->evaluator_options.evaluation_callback =
      pp->reduced_program->mutable_evaluation_callback();
  pp->evaluator = Evaluator::Create(
      pp->evaluator_options, pp->reduced_program.get(), &pp->error);
  return (pp->evaluator.get() != nullptr);
}

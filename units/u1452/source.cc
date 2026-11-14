// u1452 – ceres::internal::(anonymous)::SetupMinimizerOptions
// Trích từ internal/ceres/trust_region_preprocessor.cc, dòng 339–370 (chỉ để xem, không compile)

bool SetupMinimizerOptions(PreprocessedProblem* pp) {
  const Solver::Options& options = pp->options;

  SetupCommonMinimizerOptions(pp);
  pp->minimizer_options.is_constrained =
      pp->reduced_program->IsBoundsConstrained();
  pp->minimizer_options.jacobian = pp->evaluator->CreateJacobian();
  if (pp->minimizer_options.jacobian == nullptr) {
    pp->error =
        "Unable to create Jacobian matrix. Likely because it is too large.";
    return false;
  }

  pp->minimizer_options.inner_iteration_minimizer =
      pp->inner_iteration_minimizer;

  TrustRegionStrategy::Options strategy_options;
  strategy_options.linear_solver = pp->linear_solver.get();
  strategy_options.initial_radius = options.initial_trust_region_radius;
  strategy_options.max_radius = options.max_trust_region_radius;
  strategy_options.min_lm_diagonal = options.min_lm_diagonal;
  strategy_options.max_lm_diagonal = options.max_lm_diagonal;
  strategy_options.trust_region_strategy_type =
      options.trust_region_strategy_type;
  strategy_options.dogleg_type = options.dogleg_type;
  strategy_options.context = pp->problem->context();
  strategy_options.num_threads = options.num_threads;
  pp->minimizer_options.trust_region_strategy =
      TrustRegionStrategy::Create(strategy_options);
  CHECK(pp->minimizer_options.trust_region_strategy != nullptr);
  return true;
}

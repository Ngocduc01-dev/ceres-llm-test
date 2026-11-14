// u1493 – ceres::internal::CoordinateDescentMinimizer::Solve
// Trích từ internal/ceres/coordinate_descent_minimizer.cc, dòng 211–237 (chỉ để xem, không compile)

void CoordinateDescentMinimizer::Solve(Program* program,
                                       LinearSolver* linear_solver,
                                       double* parameter,
                                       Solver::Summary* summary) {
  *summary = Solver::Summary();
  summary->initial_cost = 0.0;
  summary->fixed_cost = 0.0;
  summary->final_cost = 0.0;
  std::string error;

  Minimizer::Options minimizer_options;
  minimizer_options.evaluator =
      Evaluator::Create(evaluator_options_, program, &error);
  CHECK(minimizer_options.evaluator != nullptr);
  minimizer_options.jacobian = minimizer_options.evaluator->CreateJacobian();
  CHECK(minimizer_options.jacobian != nullptr);

  TrustRegionStrategy::Options trs_options;
  trs_options.linear_solver = linear_solver;
  minimizer_options.trust_region_strategy =
      TrustRegionStrategy::Create(trs_options);
  CHECK(minimizer_options.trust_region_strategy != nullptr);
  minimizer_options.is_silent = true;

  TrustRegionMinimizer minimizer;
  minimizer.Minimize(minimizer_options, parameter, summary);
}

// u1495 – ceres::(anonymous)::Minimize
// Trích từ internal/ceres/solver.cc, dòng 627–654 (chỉ để xem, không compile)

void Minimize(internal::PreprocessedProblem* pp, Solver::Summary* summary) {
  using internal::Minimizer;
  using internal::Program;

  Program* program = pp->reduced_program.get();
  if (pp->reduced_program->NumParameterBlocks() == 0) {
    summary->message =
        "Function tolerance reached. "
        "No non-constant parameter blocks found.";
    summary->termination_type = CONVERGENCE;
    if (pp->options.logging_type != SILENT) {
      VLOG(1) << summary->message;
    }
    summary->initial_cost = summary->fixed_cost;
    summary->final_cost = summary->fixed_cost;
    return;
  }

  const Vector original_reduced_parameters = pp->reduced_parameters;
  auto minimizer = Minimizer::Create(pp->options.minimizer_type);
  minimizer->Minimize(
      pp->minimizer_options, pp->reduced_parameters.data(), summary);

  program->StateVectorToParameterBlocks(
      summary->IsSolutionUsable() ? pp->reduced_parameters.data()
                                  : original_reduced_parameters.data());
  program->CopyParameterBlockStateToUserState();
}

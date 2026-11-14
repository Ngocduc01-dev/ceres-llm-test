// u1412 – ceres::(anonymous)::SummarizeReducedProgram
// Trích từ internal/ceres/solver.cc, dòng 519–528 (chỉ để xem, không compile)

void SummarizeReducedProgram(const internal::Program& program,
                             Solver::Summary* summary) {
  // clang-format off
  summary->num_parameter_blocks_reduced     = program.NumParameterBlocks();
  summary->num_parameters_reduced           = program.NumParameters();
  summary->num_effective_parameters_reduced = program.NumEffectiveParameters();
  summary->num_residual_blocks_reduced      = program.NumResidualBlocks();
  summary->num_residuals_reduced            = program.NumResiduals();
  // clang-format on
}

// u1411 – ceres::(anonymous)::SummarizeGivenProgram
// Trích từ internal/ceres/solver.cc, dòng 508–517 (chỉ để xem, không compile)

void SummarizeGivenProgram(const internal::Program& program,
                           Solver::Summary* summary) {
  // clang-format off
  summary->num_parameter_blocks     = program.NumParameterBlocks();
  summary->num_parameters           = program.NumParameters();
  summary->num_effective_parameters = program.NumEffectiveParameters();
  summary->num_residual_blocks      = program.NumResidualBlocks();
  summary->num_residuals            = program.NumResiduals();
  // clang-format on
}

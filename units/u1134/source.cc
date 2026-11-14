// u1134 – ceres::internal::(anonymous)::CreateDefaultLinearSolverOrdering
// Trích từ internal/ceres/trust_region_preprocessor.cc, dòng 56–67 (chỉ để xem, không compile)

std::shared_ptr<ParameterBlockOrdering> CreateDefaultLinearSolverOrdering(
    const Program& program) {
  std::shared_ptr<ParameterBlockOrdering> ordering =
      std::make_shared<ParameterBlockOrdering>();
  const std::vector<ParameterBlock*>& parameter_blocks =
      program.parameter_blocks();
  for (auto* parameter_block : parameter_blocks) {
    ordering->AddElementToGroup(
        const_cast<double*>(parameter_block->user_state()), 0);
  }
  return ordering;
}

// u1387 – ceres::internal::Program::StateVectorToParameterBlocks
// Trích từ internal/ceres/program.cc, dòng 77–85 (chỉ để xem, không compile)

bool Program::StateVectorToParameterBlocks(const double* state) {
  for (auto* parameter_block : parameter_blocks_) {
    if (!parameter_block->IsConstant() && !parameter_block->SetState(state)) {
      return false;
    }
    state += parameter_block->Size();
  }
  return true;
}

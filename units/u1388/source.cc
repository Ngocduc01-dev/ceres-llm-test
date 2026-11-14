// u1388 – ceres::internal::Program::SetParameterBlockStatePtrsToUserStatePtrs
// Trích từ internal/ceres/program.cc, dòng 100–108 (chỉ để xem, không compile)

bool Program::SetParameterBlockStatePtrsToUserStatePtrs() {
  for (auto* parameter_block : parameter_blocks_) {
    if (!parameter_block->IsConstant() &&
        !parameter_block->SetState(parameter_block->user_state())) {
      return false;
    }
  }
  return true;
}

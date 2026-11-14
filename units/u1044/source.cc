// u1044 – ceres::internal::Program::CopyParameterBlockStateToUserState
// Trích từ internal/ceres/program.cc, dòng 94–98 (chỉ để xem, không compile)

void Program::CopyParameterBlockStateToUserState() {
  for (auto* parameter_block : parameter_blocks_) {
    parameter_block->GetState(parameter_block->mutable_user_state());
  }
}

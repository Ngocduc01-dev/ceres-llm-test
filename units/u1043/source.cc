// u1043 – ceres::internal::Program::ParameterBlocksToStateVector
// Trích từ internal/ceres/program.cc, dòng 87–92 (chỉ để xem, không compile)

void Program::ParameterBlocksToStateVector(double* state) const {
  for (auto* parameter_block : parameter_blocks_) {
    parameter_block->GetState(state);
    state += parameter_block->Size();
  }
}

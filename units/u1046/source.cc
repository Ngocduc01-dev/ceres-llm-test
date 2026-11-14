// u1046 – ceres::internal::Program::NumEffectiveParameters
// Trích từ internal/ceres/program.cc, dòng 499–505 (chỉ để xem, không compile)

int Program::NumEffectiveParameters() const {
  int num_parameters = 0;
  for (auto* parameter_block : parameter_blocks_) {
    num_parameters += parameter_block->TangentSize();
  }
  return num_parameters;
}

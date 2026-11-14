// u1045 – ceres::internal::Program::NumParameters
// Trích từ internal/ceres/program.cc, dòng 491–497 (chỉ để xem, không compile)

int Program::NumParameters() const {
  int num_parameters = 0;
  for (auto* parameter_block : parameter_blocks_) {
    num_parameters += parameter_block->Size();
  }
  return num_parameters;
}

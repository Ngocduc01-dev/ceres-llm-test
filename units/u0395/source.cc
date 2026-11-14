// u0395 – ceres::internal::Program::mutable_parameter_blocks
// Trích từ internal/ceres/program.cc, dòng 65–67 (chỉ để xem, không compile)

std::vector<ParameterBlock*>* Program::mutable_parameter_blocks() {
  return &parameter_blocks_;
}

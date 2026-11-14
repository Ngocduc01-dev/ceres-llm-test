// u1501 – ceres::internal::Program::CreateReducedProgram
// Trích từ internal/ceres/program.cc, dòng 287–303 (chỉ để xem, không compile)

std::unique_ptr<Program> Program::CreateReducedProgram(
    std::vector<double*>* removed_parameter_blocks,
    double* fixed_cost,
    std::string* error) const {
  CHECK(removed_parameter_blocks != nullptr);
  CHECK(fixed_cost != nullptr);
  CHECK(error != nullptr);

  std::unique_ptr<Program> reduced_program = std::make_unique<Program>(*this);
  if (!reduced_program->RemoveFixedBlocks(
          removed_parameter_blocks, fixed_cost, error)) {
    return nullptr;
  }

  reduced_program->SetParameterOffsetsAndIndex();
  return reduced_program;
}

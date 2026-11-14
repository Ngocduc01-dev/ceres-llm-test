// u1403 – ceres::internal::Program::ParameterBlocksAreFinite
// Trích từ internal/ceres/program.cc, dòng 190–209 (chỉ để xem, không compile)

bool Program::ParameterBlocksAreFinite(std::string* message) const {
  CHECK(message != nullptr);
  for (auto* parameter_block : parameter_blocks_) {
    const double* array = parameter_block->user_state();
    const int size = parameter_block->Size();
    const int invalid_index = FindInvalidValue(size, array);
    if (invalid_index != size) {
      *message = StringPrintf(
          "ParameterBlock: %p with size %d has at least one invalid value.\n"
          "First invalid value is at index: %d.\n"
          "Parameter block values: ",
          array,
          size,
          invalid_index);
      AppendArrayToString(size, array, message);
      return false;
    }
  }
  return true;
}

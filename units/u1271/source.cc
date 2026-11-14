// u1271 – ceres::internal::Program::IsBoundsConstrained
// Trích từ internal/ceres/program.cc, dòng 211–227 (chỉ để xem, không compile)

bool Program::IsBoundsConstrained() const {
  for (auto* parameter_block : parameter_blocks_) {
    if (parameter_block->IsConstant()) {
      continue;
    }
    const int size = parameter_block->Size();
    for (int j = 0; j < size; ++j) {
      const double lower_bound = parameter_block->LowerBoundForParameter(j);
      const double upper_bound = parameter_block->UpperBoundForParameter(j);
      if (lower_bound > -std::numeric_limits<double>::max() ||
          upper_bound < std::numeric_limits<double>::max()) {
        return true;
      }
    }
  }
  return false;
}

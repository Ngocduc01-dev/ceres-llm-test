// u1386 – ceres::internal::Program::ToString
// Trích từ internal/ceres/program.cc, dòng 552–562 (chỉ để xem, không compile)

std::string Program::ToString() const {
  std::string ret = "Program dump\n";
  ret += StringPrintf("Number of parameter blocks: %d\n", NumParameterBlocks());
  ret += StringPrintf("Number of parameters: %d\n", NumParameters());
  ret += "Parameters:\n";
  for (int i = 0; i < parameter_blocks_.size(); ++i) {
    ret +=
        StringPrintf("%d: %s\n", i, parameter_blocks_[i]->ToString().c_str());
  }
  return ret;
}

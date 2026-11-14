// u1042 – ceres::internal::ProblemImpl::ParameterBlockTangentSize
// Trích từ internal/ceres/problem_impl.cc, dòng 810–820 (chỉ để xem, không compile)

int ProblemImpl::ParameterBlockTangentSize(const double* values) const {
  ParameterBlock* parameter_block = FindWithDefault(
      parameter_block_map_, const_cast<double*>(values), nullptr);
  if (parameter_block == nullptr) {
    LOG(FATAL) << "Parameter block not found: " << values
               << ". You must add the parameter block to the problem before "
               << "you can get its tangent size.";
  }

  return parameter_block->TangentSize();
}

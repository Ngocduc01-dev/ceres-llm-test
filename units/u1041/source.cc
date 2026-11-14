// u1041 – ceres::internal::ProblemImpl::ParameterBlockSize
// Trích từ internal/ceres/problem_impl.cc, dòng 798–808 (chỉ để xem, không compile)

int ProblemImpl::ParameterBlockSize(const double* values) const {
  ParameterBlock* parameter_block = FindWithDefault(
      parameter_block_map_, const_cast<double*>(values), nullptr);
  if (parameter_block == nullptr) {
    LOG(FATAL) << "Parameter block not found: " << values
               << ". You must add the parameter block to the problem before "
               << "you can get its size.";
  }

  return parameter_block->Size();
}

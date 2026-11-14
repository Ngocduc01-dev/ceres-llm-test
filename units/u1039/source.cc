// u1039 – ceres::internal::ProblemImpl::GetParameterLowerBound
// Trích từ internal/ceres/problem_impl.cc, dòng 561–571 (chỉ để xem, không compile)

double ProblemImpl::GetParameterLowerBound(const double* values,
                                           int index) const {
  ParameterBlock* parameter_block = FindWithDefault(
      parameter_block_map_, const_cast<double*>(values), nullptr);
  if (parameter_block == nullptr) {
    LOG(FATAL) << "Parameter block not found: " << values
               << ". You must add the parameter block to the problem before "
               << "you can get the lower bound on one of its components.";
  }
  return parameter_block->LowerBound(index);
}

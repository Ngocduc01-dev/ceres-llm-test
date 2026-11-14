// u1259 – ceres::internal::ProblemImpl::IsParameterBlockConstant
// Trích từ internal/ceres/problem_impl.cc, dòng 485–492 (chỉ để xem, không compile)

bool ProblemImpl::IsParameterBlockConstant(const double* values) const {
  const ParameterBlock* parameter_block = FindWithDefault(
      parameter_block_map_, const_cast<double*>(values), nullptr);
  CHECK(parameter_block != nullptr)
      << "Parameter block not found: " << values << ". You must add the "
      << "parameter block to the problem before it can be queried.";
  return parameter_block->IsConstant();
}

// u1036 – ceres::internal::ProblemImpl::SetParameterBlockVariable
// Trích từ internal/ceres/problem_impl.cc, dòng 494–504 (chỉ để xem, không compile)

void ProblemImpl::SetParameterBlockVariable(double* values) {
  ParameterBlock* parameter_block =
      FindWithDefault(parameter_block_map_, values, nullptr);
  if (parameter_block == nullptr) {
    LOG(FATAL) << "Parameter block not found: " << values
               << ". You must add the parameter block to the problem before "
               << "it can be set varying.";
  }

  parameter_block->SetVarying();
}

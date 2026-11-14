// u1035 – ceres::internal::ProblemImpl::SetParameterBlockConstant
// Trích từ internal/ceres/problem_impl.cc, dòng 473–483 (chỉ để xem, không compile)

void ProblemImpl::SetParameterBlockConstant(const double* values) {
  ParameterBlock* parameter_block = FindWithDefault(
      parameter_block_map_, const_cast<double*>(values), nullptr);
  if (parameter_block == nullptr) {
    LOG(FATAL) << "Parameter block not found: " << values
               << ". You must add the parameter block to the problem before "
               << "it can be set constant.";
  }

  parameter_block->SetConstant();
}

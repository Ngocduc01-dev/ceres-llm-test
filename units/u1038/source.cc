// u1038 – ceres::internal::ProblemImpl::SetParameterUpperBound
// Trích từ internal/ceres/problem_impl.cc, dòng 548–559 (chỉ để xem, không compile)

void ProblemImpl::SetParameterUpperBound(double* values,
                                         int index,
                                         double upper_bound) {
  ParameterBlock* parameter_block =
      FindWithDefault(parameter_block_map_, values, nullptr);
  if (parameter_block == nullptr) {
    LOG(FATAL) << "Parameter block not found: " << values
               << ". You must add the parameter block to the problem before "
               << "you can set an upper bound on one of its components.";
  }
  parameter_block->SetUpperBound(index, upper_bound);
}

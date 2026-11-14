// u1037 – ceres::internal::ProblemImpl::SetParameterLowerBound
// Trích từ internal/ceres/problem_impl.cc, dòng 534–546 (chỉ để xem, không compile)

void ProblemImpl::SetParameterLowerBound(double* values,
                                         int index,
                                         double lower_bound) {
  ParameterBlock* parameter_block =
      FindWithDefault(parameter_block_map_, values, nullptr);
  if (parameter_block == nullptr) {
    LOG(FATAL) << "Parameter block not found: " << values
               << ". You must add the parameter block to the problem before "
               << "you can set a lower bound on one of its components.";
  }

  parameter_block->SetLowerBound(index, lower_bound);
}

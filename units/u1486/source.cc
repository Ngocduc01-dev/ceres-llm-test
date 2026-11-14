// u1486 – ceres::internal::ProblemImpl::SetManifold
// Trích từ internal/ceres/problem_impl.cc, dòng 506–516 (chỉ để xem, không compile)

void ProblemImpl::SetManifold(double* values, Manifold* manifold) {
  ParameterBlock* parameter_block =
      FindWithDefault(parameter_block_map_, values, nullptr);
  if (parameter_block == nullptr) {
    LOG(FATAL) << "Parameter block not found: " << values
               << ". You must add the parameter block to the problem before "
               << "you can set its manifold.";
  }

  InternalSetManifold(values, parameter_block, manifold);
}

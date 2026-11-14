// u1164 – ceres::internal::ProblemImpl::GetManifold
// Trích từ internal/ceres/problem_impl.cc, dòng 518–528 (chỉ để xem, không compile)

const Manifold* ProblemImpl::GetManifold(const double* values) const {
  ParameterBlock* parameter_block = FindWithDefault(
      parameter_block_map_, const_cast<double*>(values), nullptr);
  if (parameter_block == nullptr) {
    LOG(FATAL) << "Parameter block not found: " << values
               << ". You must add the parameter block to the problem before "
               << "you can get its manifold.";
  }

  return parameter_block->manifold();
}

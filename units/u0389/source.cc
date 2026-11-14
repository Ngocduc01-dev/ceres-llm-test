// u0389 – ceres::internal::ProblemImpl::HasParameterBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 822–825 (chỉ để xem, không compile)

bool ProblemImpl::HasParameterBlock(const double* values) const {
  return (parameter_block_map_.find(const_cast<double*>(values)) !=
          parameter_block_map_.end());
}

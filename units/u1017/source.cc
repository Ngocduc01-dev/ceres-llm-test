// u1017 – ceres::internal::ProblemImpl::NumParameterBlocks
// Trích từ internal/ceres/problem_impl.cc, dòng 786–788 (chỉ để xem, không compile)

int ProblemImpl::NumParameterBlocks() const {
  return program_->NumParameterBlocks();
}

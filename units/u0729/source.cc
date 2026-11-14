// u0729 – ceres::internal::ProblemImpl::GetParameterBlocks
// Trích từ internal/ceres/problem_impl.cc, dòng 827–835 (chỉ để xem, không compile)

void ProblemImpl::GetParameterBlocks(
    std::vector<double*>* parameter_blocks) const {
  CHECK(parameter_blocks != nullptr);
  parameter_blocks->resize(0);
  parameter_blocks->reserve(parameter_block_map_.size());
  for (const auto& entry : parameter_block_map_) {
    parameter_blocks->push_back(entry.first);
  }
}

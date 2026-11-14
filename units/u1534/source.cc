// u1534 – ceres::internal::CovarianceImpl::Compute
// Trích từ internal/ceres/covariance_impl.cc, dòng 114–126 (chỉ để xem, không compile)

bool CovarianceImpl::Compute(const std::vector<const double*>& parameter_blocks,
                             ProblemImpl* problem) {
  CheckForDuplicates<const double*>(parameter_blocks);
  CovarianceBlocks covariance_blocks;
  for (int i = 0; i < parameter_blocks.size(); ++i) {
    for (int j = i; j < parameter_blocks.size(); ++j) {
      covariance_blocks.push_back(
          std::make_pair(parameter_blocks[i], parameter_blocks[j]));
    }
  }

  return Compute(covariance_blocks, problem);
}

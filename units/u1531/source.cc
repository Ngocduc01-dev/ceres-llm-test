// u1531 – ceres::internal::CovarianceImpl::Compute
// Trích từ internal/ceres/covariance_impl.cc, dòng 101–112 (chỉ để xem, không compile)

bool CovarianceImpl::Compute(const CovarianceBlocks& covariance_blocks,
                             ProblemImpl* problem) {
  CheckForDuplicates<std::pair<const double*, const double*>>(
      covariance_blocks);
  problem_ = problem;
  parameter_block_to_row_index_.clear();
  covariance_matrix_ = nullptr;
  is_valid_ = (ComputeCovarianceSparsity(covariance_blocks, problem) &&
               ComputeCovarianceValues());
  is_computed_ = true;
  return is_valid_;
}

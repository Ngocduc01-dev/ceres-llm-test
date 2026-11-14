// u0485 – ceres::internal::ProblemImpl::residual_block_set
// Trích từ internal/ceres/problem_impl.h, dòng 163–167 (chỉ để xem, không compile)

  const ResidualBlockSet& residual_block_set() const {
    CHECK(options_.enable_fast_removal)
        << "Fast removal not enabled, residual_block_set is not maintained.";
    return residual_block_set_;
  }

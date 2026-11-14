// u1089 – ceres::internal::ProblemImpl::GetResidualBlocks
// Trích từ internal/ceres/problem_impl.cc, dòng 837–841 (chỉ để xem, không compile)

void ProblemImpl::GetResidualBlocks(
    std::vector<ResidualBlockId>* residual_blocks) const {
  CHECK(residual_blocks != nullptr);
  *residual_blocks = program().residual_blocks();
}

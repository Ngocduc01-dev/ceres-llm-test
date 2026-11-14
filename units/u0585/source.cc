// u0585 – ceres::internal::VisibilityBasedPreconditioner::IsBlockPairOffDiagonal
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 448–451 (chỉ để xem, không compile)

bool VisibilityBasedPreconditioner::IsBlockPairOffDiagonal(
    const int block1, const int block2) const {
  return (cluster_membership_[block1] != cluster_membership_[block2]);
}

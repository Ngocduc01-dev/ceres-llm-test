// u0603 – ceres::internal::VisibilityBasedPreconditioner::IsBlockPairInPreconditioner
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 438–446 (chỉ để xem, không compile)

bool VisibilityBasedPreconditioner::IsBlockPairInPreconditioner(
    const int block1, const int block2) const {
  int cluster1 = cluster_membership_[block1];
  int cluster2 = cluster_membership_[block2];
  if (cluster1 > cluster2) {
    std::swap(cluster1, cluster2);
  }
  return (cluster_pairs_.count(std::make_pair(cluster1, cluster2)) > 0);
}

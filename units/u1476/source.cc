// u1476 – ceres::internal::VisibilityBasedPreconditioner::ComputeClusterJacobiSparsity
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 118–128 (chỉ để xem, không compile)

void VisibilityBasedPreconditioner::ComputeClusterJacobiSparsity(
    const CompressedRowBlockStructure& bs) {
  std::vector<std::set<int>> visibility;
  ComputeVisibility(bs, options_.elimination_groups[0], &visibility);
  CHECK_EQ(num_blocks_, visibility.size());
  ClusterCameras(visibility);
  cluster_pairs_.clear();
  for (int i = 0; i < num_clusters_; ++i) {
    cluster_pairs_.insert(std::make_pair(i, i));
  }
}

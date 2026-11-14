// u0805 – ceres::internal::VisibilityBasedPreconditioner::ComputeClusterVisibility
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 479–490 (chỉ để xem, không compile)

void VisibilityBasedPreconditioner::ComputeClusterVisibility(
    const std::vector<std::set<int>>& visibility,
    std::vector<std::set<int>>* cluster_visibility) const {
  CHECK(cluster_visibility != nullptr);
  cluster_visibility->resize(0);
  cluster_visibility->resize(num_clusters_);
  for (int i = 0; i < num_blocks_; ++i) {
    const int cluster_id = cluster_membership_[i];
    (*cluster_visibility)[cluster_id].insert(visibility[i].begin(),
                                             visibility[i].end());
  }
}

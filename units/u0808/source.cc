// u0808 – ceres::internal::CanonicalViewsClustering::ComputeClusterMembership
// Trích từ internal/ceres/canonical_views_clustering.cc, dòng 198–221 (chỉ để xem, không compile)

void CanonicalViewsClustering::ComputeClusterMembership(
    const std::vector<int>& centers, IntMap* membership) const {
  CHECK(membership != nullptr);
  membership->clear();

  // The i^th cluster has cluster id i.
  IntMap center_to_cluster_id;
  for (int i = 0; i < centers.size(); ++i) {
    center_to_cluster_id[centers[i]] = i;
  }

  static constexpr int kInvalidClusterId = -1;

  const IntSet& views = graph_->vertices();
  for (const auto& view : views) {
    auto it = view_to_canonical_view_.find(view);
    int cluster_id = kInvalidClusterId;
    if (it != view_to_canonical_view_.end()) {
      cluster_id = FindOrDie(center_to_cluster_id, it->second);
    }

    InsertOrDie(membership, view, cluster_id);
  }
}

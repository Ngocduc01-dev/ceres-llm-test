// u0811 – ceres::internal::VisibilityBasedPreconditioner::ForestToClusterPairs
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 455–474 (chỉ để xem, không compile)

void VisibilityBasedPreconditioner::ForestToClusterPairs(
    const WeightedGraph<int>& forest,
    std::unordered_set<std::pair<int, int>, pair_hash>* cluster_pairs) const {
  CHECK(cluster_pairs != nullptr);
  cluster_pairs->clear();
  const std::unordered_set<int>& vertices = forest.vertices();
  CHECK_EQ(vertices.size(), num_clusters_);

  // Add all the cluster pairs corresponding to the edges in the
  // forest.
  for (const int cluster1 : vertices) {
    cluster_pairs->insert(std::make_pair(cluster1, cluster1));
    const std::unordered_set<int>& neighbors = forest.Neighbors(cluster1);
    for (const int cluster2 : neighbors) {
      if (cluster1 < cluster2) {
        cluster_pairs->insert(std::make_pair(cluster1, cluster2));
      }
    }
  }
}

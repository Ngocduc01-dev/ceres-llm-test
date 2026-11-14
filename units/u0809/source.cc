// u0809 – ceres::internal::VisibilityBasedPreconditioner::CreateClusterGraph
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 495–526 (chỉ để xem, không compile)

std::unique_ptr<WeightedGraph<int>>
VisibilityBasedPreconditioner::CreateClusterGraph(
    const std::vector<std::set<int>>& cluster_visibility) const {
  auto cluster_graph = std::make_unique<WeightedGraph<int>>();

  for (int i = 0; i < num_clusters_; ++i) {
    cluster_graph->AddVertex(i);
  }

  for (int i = 0; i < num_clusters_; ++i) {
    const std::set<int>& cluster_i = cluster_visibility[i];
    for (int j = i + 1; j < num_clusters_; ++j) {
      std::vector<int> intersection;
      const std::set<int>& cluster_j = cluster_visibility[j];
      std::set_intersection(cluster_i.begin(),
                            cluster_i.end(),
                            cluster_j.begin(),
                            cluster_j.end(),
                            std::back_inserter(intersection));

      if (intersection.size() > 0) {
        // Clusters interact strongly when they share a large number
        // of 3D points. The degree-2 maximum spanning forest
        // algorithm, iterates on the edges in decreasing order of
        // their weight, which is the number of points shared by the
        // two cameras that it connects.
        cluster_graph->AddEdge(i, j, intersection.size());
      }
    }
  }
  return cluster_graph;
}

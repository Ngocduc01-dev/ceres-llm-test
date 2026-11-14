// u0781 – ceres::internal::ComputeSingleLinkageClustering
// Trích từ internal/ceres/single_linkage_clustering.cc, dòng 41–91 (chỉ để xem, không compile)

int ComputeSingleLinkageClustering(
    const SingleLinkageClusteringOptions& options,
    const WeightedGraph<int>& graph,
    std::unordered_map<int, int>* membership) {
  CHECK(membership != nullptr);
  membership->clear();

  // Initially each vertex is in its own cluster.
  const std::unordered_set<int>& vertices = graph.vertices();
  for (const int v : vertices) {
    (*membership)[v] = v;
  }

  for (const int vertex1 : vertices) {
    const std::unordered_set<int>& neighbors = graph.Neighbors(vertex1);
    for (const int vertex2 : neighbors) {
      // Since the graph is undirected, only pay attention to one side
      // of the edge and ignore weak edges.
      if ((vertex1 > vertex2) ||
          (graph.EdgeWeight(vertex1, vertex2) < options.min_similarity)) {
        continue;
      }

      // Use a union-find algorithm to keep track of the clusters.
      const int c1 = FindConnectedComponent(vertex1, membership);
      const int c2 = FindConnectedComponent(vertex2, membership);

      if (c1 == c2) {
        continue;
      }

      if (c1 < c2) {
        (*membership)[c2] = c1;
      } else {
        (*membership)[c1] = c2;
      }
    }
  }

  // Make sure that every vertex is connected directly to the vertex
  // identifying the cluster.
  int num_clusters = 0;
  for (auto& m : *membership) {
    m.second = FindConnectedComponent(m.first, membership);
    if (m.first == m.second) {
      ++num_clusters;
    }
  }

  return num_clusters;
}

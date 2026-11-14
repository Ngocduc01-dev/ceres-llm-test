// u1286 – ceres::internal::ComputeCanonicalViewsClustering
// Trích từ internal/ceres/canonical_views_clustering.cc, dòng 80–90 (chỉ để xem, không compile)

void ComputeCanonicalViewsClustering(
    const CanonicalViewsClusteringOptions& options,
    const WeightedGraph<int>& graph,
    std::vector<int>* centers,
    IntMap* membership) {
  time_t start_time = time(nullptr);
  CanonicalViewsClustering cv;
  cv.ComputeClustering(options, graph, centers, membership);
  VLOG(2) << "Canonical views clustering time (secs): "
          << time(nullptr) - start_time;
}

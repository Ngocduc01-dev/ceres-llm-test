// u1126 – ceres::internal::CanonicalViewsClustering::ComputeClustering
// Trích từ internal/ceres/canonical_views_clustering.cc, dòng 93–136 (chỉ để xem, không compile)

void CanonicalViewsClustering::ComputeClustering(
    const CanonicalViewsClusteringOptions& options,
    const WeightedGraph<int>& graph,
    std::vector<int>* centers,
    IntMap* membership) {
  options_ = options;
  CHECK(centers != nullptr);
  CHECK(membership != nullptr);
  centers->clear();
  membership->clear();
  graph_ = &graph;

  IntSet valid_views;
  FindValidViews(&valid_views);
  while (!valid_views.empty()) {
    // Find the next best canonical view.
    double best_difference = -std::numeric_limits<double>::max();
    int best_view = 0;

    // TODO(sameeragarwal): Make this loop multi-threaded.
    for (const auto& view : valid_views) {
      const double difference =
          ComputeClusteringQualityDifference(view, *centers);
      if (difference > best_difference) {
        best_difference = difference;
        best_view = view;
      }
    }

    CHECK_GT(best_difference, -std::numeric_limits<double>::max());

    // Add canonical view if quality improves, or if minimum is not
    // yet met, otherwise break.
    if ((best_difference <= 0) && (centers->size() >= options_.min_views)) {
      break;
    }

    centers->push_back(best_view);
    valid_views.erase(best_view);
    UpdateCanonicalViewAssignments(best_view);
  }

  ComputeClusterMembership(*centers, membership);
}

// u0803 – ceres::internal::CanonicalViewsClustering::FindValidViews
// Trích từ internal/ceres/canonical_views_clustering.cc, dòng 140–147 (chỉ để xem, không compile)

void CanonicalViewsClustering::FindValidViews(IntSet* valid_views) const {
  const IntSet& views = graph_->vertices();
  for (const auto& view : views) {
    if (graph_->VertexWeight(view) != WeightedGraph<int>::InvalidWeight()) {
      valid_views->insert(view);
    }
  }
}

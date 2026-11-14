// u0604 – ceres::internal::CanonicalViewsClustering::UpdateCanonicalViewAssignments
// Trích từ internal/ceres/canonical_views_clustering.cc, dòng 183–195 (chỉ để xem, không compile)

void CanonicalViewsClustering::UpdateCanonicalViewAssignments(
    const int canonical_view) {
  const IntSet& neighbors = graph_->Neighbors(canonical_view);
  for (const auto& neighbor : neighbors) {
    const double old_similarity =
        FindWithDefault(view_to_canonical_view_similarity_, neighbor, 0.0);
    const double new_similarity = graph_->EdgeWeight(neighbor, canonical_view);
    if (new_similarity > old_similarity) {
      view_to_canonical_view_[neighbor] = canonical_view;
      view_to_canonical_view_similarity_[neighbor] = new_similarity;
    }
  }
}

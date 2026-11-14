// u0806 – ceres::internal::CanonicalViewsClustering::ComputeClusteringQualityDifference
// Trích từ internal/ceres/canonical_views_clustering.cc, dòng 151–180 (chỉ để xem, không compile)

double CanonicalViewsClustering::ComputeClusteringQualityDifference(
    const int candidate, const std::vector<int>& centers) const {
  // View score.
  double difference =
      options_.view_score_weight * graph_->VertexWeight(candidate);

  // Compute how much the quality score changes if the candidate view
  // was added to the list of canonical views and its nearest
  // neighbors became members of its cluster.
  const IntSet& neighbors = graph_->Neighbors(candidate);
  for (const auto& neighbor : neighbors) {
    const double old_similarity =
        FindWithDefault(view_to_canonical_view_similarity_, neighbor, 0.0);
    const double new_similarity = graph_->EdgeWeight(neighbor, candidate);
    if (new_similarity > old_similarity) {
      difference += new_similarity - old_similarity;
    }
  }

  // Number of views penalty.
  difference -= options_.size_penalty_weight;

  // Orthogonality.
  for (int center : centers) {
    difference -= options_.similarity_penalty_weight *
                  graph_->EdgeWeight(center, candidate);
  }

  return difference;
}

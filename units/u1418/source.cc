// u1418 – ceres::internal::VisibilityBasedPreconditioner::ClusterCameras
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 170–198 (chỉ để xem, không compile)

void VisibilityBasedPreconditioner::ClusterCameras(
    const std::vector<std::set<int>>& visibility) {
  auto schur_complement_graph = CreateSchurComplementGraph(visibility);
  CHECK(schur_complement_graph != nullptr);

  std::unordered_map<int, int> membership;

  if (options_.visibility_clustering_type == CANONICAL_VIEWS) {
    std::vector<int> centers;
    CanonicalViewsClusteringOptions clustering_options;
    clustering_options.size_penalty_weight = kCanonicalViewsSizePenaltyWeight;
    clustering_options.similarity_penalty_weight =
        kCanonicalViewsSimilarityPenaltyWeight;
    ComputeCanonicalViewsClustering(
        clustering_options, *schur_complement_graph, &centers, &membership);
    num_clusters_ = centers.size();
  } else if (options_.visibility_clustering_type == SINGLE_LINKAGE) {
    SingleLinkageClusteringOptions clustering_options;
    clustering_options.min_similarity = kSingleLinkageMinSimilarity;
    num_clusters_ = ComputeSingleLinkageClustering(
        clustering_options, *schur_complement_graph, &membership);
  } else {
    LOG(FATAL) << "Unknown visibility clustering algorithm.";
  }

  CHECK_GT(num_clusters_, 0);
  VLOG(2) << "num_clusters: " << num_clusters_;
  FlattenMembershipMap(membership, &cluster_membership_);
}

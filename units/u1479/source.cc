// u1479 – ceres::internal::VisibilityBasedPreconditioner::ComputeClusterTridiagonalSparsity
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 136–154 (chỉ để xem, không compile)

void VisibilityBasedPreconditioner::ComputeClusterTridiagonalSparsity(
    const CompressedRowBlockStructure& bs) {
  std::vector<std::set<int>> visibility;
  ComputeVisibility(bs, options_.elimination_groups[0], &visibility);
  CHECK_EQ(num_blocks_, visibility.size());
  ClusterCameras(visibility);

  // Construct a weighted graph on the set of clusters, where the
  // edges are the number of 3D points/e_blocks visible in both the
  // clusters at the ends of the edge. Return an approximate degree-2
  // maximum spanning forest of this graph.
  std::vector<std::set<int>> cluster_visibility;
  ComputeClusterVisibility(visibility, &cluster_visibility);
  auto cluster_graph = CreateClusterGraph(cluster_visibility);
  CHECK(cluster_graph != nullptr);
  auto forest = Degree2MaximumSpanningForest(*cluster_graph);
  CHECK(forest != nullptr);
  ForestToClusterPairs(*forest, &cluster_pairs_);
}

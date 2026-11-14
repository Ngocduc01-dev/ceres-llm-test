// u0784 – ceres::internal::CreateSchurComplementGraph
// Trích từ internal/ceres/visibility.cc, dòng 76–145 (chỉ để xem, không compile)

std::unique_ptr<WeightedGraph<int>> CreateSchurComplementGraph(
    const std::vector<std::set<int>>& visibility) {
  const time_t start_time = time(nullptr);
  // Compute the number of e_blocks/point blocks. Since the visibility
  // set for each e_block/camera contains the set of e_blocks/points
  // visible to it, we find the maximum across all visibility sets.
  int num_points = 0;
  for (const auto& visible : visibility) {
    if (!visible.empty()) {
      num_points = std::max(num_points, (*visible.rbegin()) + 1);
    }
  }

  // Invert the visibility. The input is a camera->point mapping,
  // which tells us which points are visible in which
  // cameras. However, to compute the sparsity structure of the Schur
  // Complement efficiently, its better to have the point->camera
  // mapping.
  std::vector<std::set<int>> inverse_visibility(num_points);
  for (int i = 0; i < visibility.size(); i++) {
    const std::set<int>& visibility_set = visibility[i];
    for (int v : visibility_set) {
      inverse_visibility[v].insert(i);
    }
  }

  // Map from camera pairs to number of points visible to both cameras
  // in the pair.
  std::unordered_map<std::pair<int, int>, int, pair_hash> camera_pairs;

  // Count the number of points visible to each camera/f_block pair.
  for (const auto& inverse_visibility_set : inverse_visibility) {
    for (auto camera1 = inverse_visibility_set.begin();
         camera1 != inverse_visibility_set.end();
         ++camera1) {
      auto camera2 = camera1;
      for (++camera2; camera2 != inverse_visibility_set.end(); ++camera2) {
        ++(camera_pairs[std::make_pair(*camera1, *camera2)]);
      }
    }
  }

  auto graph = std::make_unique<WeightedGraph<int>>();

  // Add vertices and initialize the pairs for self edges so that self
  // edges are guaranteed. This is needed for the Canonical views
  // algorithm to work correctly.
  static constexpr double kSelfEdgeWeight = 1.0;
  for (int i = 0; i < visibility.size(); ++i) {
    graph->AddVertex(i);
    graph->AddEdge(i, i, kSelfEdgeWeight);
  }

  // Add an edge for each camera pair.
  for (const auto& camera_pair_count : camera_pairs) {
    const int camera1 = camera_pair_count.first.first;
    const int camera2 = camera_pair_count.first.second;
    const int count = camera_pair_count.second;
    DCHECK_NE(camera1, camera2);
    // Static cast necessary for Windows.
    const double weight =
        static_cast<double>(count) /
        (sqrt(static_cast<double>(visibility[camera1].size() *
                                  visibility[camera2].size())));
    graph->AddEdge(camera1, camera2, weight);
  }

  VLOG(2) << "Schur complement graph time: " << (time(nullptr) - start_time);
  return graph;
}

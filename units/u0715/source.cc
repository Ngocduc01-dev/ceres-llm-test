// u0715 – ceres::internal::WeightedGraph::EdgeWeight
// Trích từ internal/ceres/graph.h, dòng 178–186 (chỉ để xem, không compile)

  double EdgeWeight(const Vertex& vertex1, const Vertex& vertex2) const {
    if (vertex1 < vertex2) {
      return FindWithDefault(
          edge_weights_, std::make_pair(vertex1, vertex2), 0.0);
    } else {
      return FindWithDefault(
          edge_weights_, std::make_pair(vertex2, vertex1), 0.0);
    }
  }

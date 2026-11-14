// u0676 – ceres::internal::WeightedGraph::Neighbors
// Trích từ internal/ceres/graph.h, dòng 190–192 (chỉ để xem, không compile)

  const std::unordered_set<Vertex>& Neighbors(const Vertex& vertex) const {
    return FindOrDie(edges_, vertex);
  }

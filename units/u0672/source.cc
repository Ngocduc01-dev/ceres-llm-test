// u0672 – ceres::internal::Graph::Neighbors
// Trích từ internal/ceres/graph.h, dòng 91–93 (chỉ để xem, không compile)

  const std::unordered_set<Vertex>& Neighbors(const Vertex& vertex) const {
    return FindOrDie(edges_, vertex);
  }

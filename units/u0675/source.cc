// u0675 – ceres::internal::WeightedGraph::VertexWeight
// Trích từ internal/ceres/graph.h, dòng 170–172 (chỉ để xem, không compile)

  double VertexWeight(const Vertex& vertex) const {
    return FindOrDie(vertex_weights_, vertex);
  }

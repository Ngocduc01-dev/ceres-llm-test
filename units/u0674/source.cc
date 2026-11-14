// u0674 – ceres::internal::WeightedGraph::AddEdge
// Trích từ internal/ceres/graph.h, dòng 164–166 (chỉ để xem, không compile)

  void AddEdge(const Vertex& vertex1, const Vertex& vertex2) {
    AddEdge(vertex1, vertex2, 1.0);
  }

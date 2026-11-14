// u0713 – ceres::internal::Graph::AddVertex
// Trích từ internal/ceres/graph.h, dòng 53–57 (chỉ để xem, không compile)

  void AddVertex(const Vertex& vertex) {
    if (vertices_.insert(vertex).second) {
      edges_[vertex] = std::unordered_set<Vertex>();
    }
  }

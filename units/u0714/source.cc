// u0714 – ceres::internal::WeightedGraph::AddVertex
// Trích từ internal/ceres/graph.h, dòng 109–115 (chỉ để xem, không compile)

  void AddVertex(const Vertex& vertex, double weight) {
    if (vertices_.find(vertex) == vertices_.end()) {
      vertices_.insert(vertex);
      edges_[vertex] = std::unordered_set<Vertex>();
    }
    vertex_weights_[vertex] = weight;
  }

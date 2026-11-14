// u0726 – ceres::internal::Graph::RemoveVertex
// Trích từ internal/ceres/graph.h, dòng 59–72 (chỉ để xem, không compile)

  bool RemoveVertex(const Vertex& vertex) {
    if (vertices_.find(vertex) == vertices_.end()) {
      return false;
    }

    vertices_.erase(vertex);
    const std::unordered_set<Vertex>& sinks = edges_[vertex];
    for (const Vertex& s : sinks) {
      edges_[s].erase(vertex);
    }

    edges_.erase(vertex);
    return true;
  }

// u0749 – ceres::internal::WeightedGraph::RemoveVertex
// Trích từ internal/ceres/graph.h, dòng 121–140 (chỉ để xem, không compile)

  bool RemoveVertex(const Vertex& vertex) {
    if (vertices_.find(vertex) == vertices_.end()) {
      return false;
    }

    vertices_.erase(vertex);
    vertex_weights_.erase(vertex);
    const std::unordered_set<Vertex>& sinks = edges_[vertex];
    for (const Vertex& s : sinks) {
      if (vertex < s) {
        edge_weights_.erase(std::make_pair(vertex, s));
      } else {
        edge_weights_.erase(std::make_pair(s, vertex));
      }
      edges_[s].erase(vertex);
    }

    edges_.erase(vertex);
    return true;
  }

// u0761 – ceres::internal::WeightedGraph::AddEdge
// Trích từ internal/ceres/graph.h, dòng 148–161 (chỉ để xem, không compile)

  void AddEdge(const Vertex& vertex1, const Vertex& vertex2, double weight) {
    DCHECK(vertices_.find(vertex1) != vertices_.end());
    DCHECK(vertices_.find(vertex2) != vertices_.end());

    if (edges_[vertex1].insert(vertex2).second) {
      edges_[vertex2].insert(vertex1);
    }

    if (vertex1 < vertex2) {
      edge_weights_[std::make_pair(vertex1, vertex2)] = weight;
    } else {
      edge_weights_[std::make_pair(vertex2, vertex1)] = weight;
    }
  }

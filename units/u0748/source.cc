// u0748 – ceres::internal::Graph::AddEdge
// Trích từ internal/ceres/graph.h, dòng 80–87 (chỉ để xem, không compile)

  void AddEdge(const Vertex& vertex1, const Vertex& vertex2) {
    DCHECK(vertices_.find(vertex1) != vertices_.end());
    DCHECK(vertices_.find(vertex2) != vertices_.end());

    if (edges_[vertex1].insert(vertex2).second) {
      edges_[vertex2].insert(vertex1);
    }
  }

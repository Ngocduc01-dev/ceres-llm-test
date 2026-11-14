// u0716 – ceres::internal::VertexTotalOrdering::operator()
// Trích từ internal/ceres/graph_algorithms.h, dòng 57–62 (chỉ để xem, không compile)

  bool operator()(const Vertex& lhs, const Vertex& rhs) const {
    if (graph_.Neighbors(lhs).size() == graph_.Neighbors(rhs).size()) {
      return lhs < rhs;
    }
    return graph_.Neighbors(lhs).size() < graph_.Neighbors(rhs).size();
  }

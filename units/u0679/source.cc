// u0679 – ceres::internal::VertexDegreeLessThan::operator()
// Trích từ internal/ceres/graph_algorithms.h, dòng 73–75 (chỉ để xem, không compile)

  bool operator()(const Vertex& lhs, const Vertex& rhs) const {
    return graph_.Neighbors(lhs).size() < graph_.Neighbors(rhs).size();
  }

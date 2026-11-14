// u0311 – ceres::internal::WeightedGraph::InvalidWeight
// Trích từ internal/ceres/graph.h, dòng 196–198 (chỉ để xem, không compile)

  static double InvalidWeight() {
    return std::numeric_limits<double>::quiet_NaN();
  }

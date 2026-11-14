// u0506 – ceres::internal::FindConnectedComponent
// Trích từ internal/ceres/graph_algorithms.h, dòng 230–240 (chỉ để xem, không compile)

template <typename Vertex>
Vertex FindConnectedComponent(const Vertex& vertex,
                              std::unordered_map<Vertex, Vertex>* union_find) {
  auto it = union_find->find(vertex);
  DCHECK(it != union_find->end());
  if (it->second != vertex) {
    it->second = FindConnectedComponent(it->second, union_find);
  }

  return it->second;
}

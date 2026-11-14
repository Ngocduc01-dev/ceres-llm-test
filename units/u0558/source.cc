// u0558 – ceres::internal::StableIndependentSetOrdering
// Trích từ internal/ceres/graph_algorithms.h, dòng 165–222 (chỉ để xem, không compile)

template <typename Vertex>
int StableIndependentSetOrdering(const Graph<Vertex>& graph,
                                 std::vector<Vertex>* ordering) {
  CHECK(ordering != nullptr);
  const std::unordered_set<Vertex>& vertices = graph.vertices();
  const int num_vertices = vertices.size();
  CHECK_EQ(vertices.size(), ordering->size());

  // Colors for labeling the graph during the BFS.
  const char kWhite = 0;
  const char kGrey = 1;
  const char kBlack = 2;

  std::vector<Vertex> vertex_queue(*ordering);

  std::stable_sort(vertex_queue.begin(),
                   vertex_queue.end(),
                   VertexDegreeLessThan<Vertex>(graph));

  // Mark all vertices white.
  std::unordered_map<Vertex, char> vertex_color;
  for (const Vertex& vertex : vertices) {
    vertex_color[vertex] = kWhite;
  }

  ordering->clear();
  ordering->reserve(num_vertices);
  // Iterate over vertex_queue. Pick the first white vertex, add it
  // to the independent set. Mark it black and its neighbors grey.
  for (int i = 0; i < vertex_queue.size(); ++i) {
    const Vertex& vertex = vertex_queue[i];
    if (vertex_color[vertex] != kWhite) {
      continue;
    }

    ordering->push_back(vertex);
    vertex_color[vertex] = kBlack;
    const std::unordered_set<Vertex>& neighbors = graph.Neighbors(vertex);
    for (const Vertex& neighbor : neighbors) {
      vertex_color[neighbor] = kGrey;
    }
  }

  int independent_set_size = ordering->size();

  // Iterate over the vertices and add all the grey vertices to the
  // ordering. At this stage there should only be black or grey
  // vertices in the graph.
  for (const Vertex& vertex : vertex_queue) {
    DCHECK(vertex_color[vertex] != kWhite);
    if (vertex_color[vertex] != kBlack) {
      ordering->push_back(vertex);
    }
  }

  CHECK_EQ(ordering->size(), num_vertices);
  return independent_set_size;
}

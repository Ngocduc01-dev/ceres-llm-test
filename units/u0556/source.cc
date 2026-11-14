// u0556 – ceres::internal::Degree2MaximumSpanningForest
// Trích từ internal/ceres/graph_algorithms.h, dòng 260–340 (chỉ để xem, không compile)

template <typename Vertex>
std::unique_ptr<WeightedGraph<Vertex>> Degree2MaximumSpanningForest(
    const WeightedGraph<Vertex>& graph) {
  // Array of edges sorted in decreasing order of their weights.
  std::vector<std::pair<double, std::pair<Vertex, Vertex>>> weighted_edges;
  auto forest = std::make_unique<WeightedGraph<Vertex>>();

  // Disjoint-set to keep track of the connected components in the
  // maximum spanning tree.
  std::unordered_map<Vertex, Vertex> disjoint_set;

  // Sort of the edges in the graph in decreasing order of their
  // weight. Also add the vertices of the graph to the Maximum
  // Spanning Tree graph and set each vertex to be its own connected
  // component in the disjoint_set structure.
  const std::unordered_set<Vertex>& vertices = graph.vertices();
  for (const Vertex& vertex1 : vertices) {
    forest->AddVertex(vertex1, graph.VertexWeight(vertex1));
    disjoint_set[vertex1] = vertex1;

    const std::unordered_set<Vertex>& neighbors = graph.Neighbors(vertex1);
    for (const Vertex& vertex2 : neighbors) {
      if (vertex1 >= vertex2) {
        continue;
      }
      const double weight = graph.EdgeWeight(vertex1, vertex2);
      weighted_edges.push_back(
          std::make_pair(weight, std::make_pair(vertex1, vertex2)));
    }
  }

  // The elements of this vector, are pairs<edge_weight,
  // edge>. Sorting it using the reverse iterators gives us the edges
  // in decreasing order of edges.
  std::sort(weighted_edges.rbegin(), weighted_edges.rend());

  // Greedily add edges to the spanning tree/forest as long as they do
  // not violate the degree/cycle constraint.
  for (int i = 0; i < weighted_edges.size(); ++i) {
    const std::pair<Vertex, Vertex>& edge = weighted_edges[i].second;
    const Vertex vertex1 = edge.first;
    const Vertex vertex2 = edge.second;

    // Check if either of the vertices are of degree 2 already, in
    // which case adding this edge will violate the degree 2
    // constraint.
    if ((forest->Neighbors(vertex1).size() == 2) ||
        (forest->Neighbors(vertex2).size() == 2)) {
      continue;
    }

    // Find the id of the connected component to which the two
    // vertices belong to. If the id is the same, it means that the
    // two of them are already connected to each other via some other
    // vertex, and adding this edge will create a cycle.
    Vertex root1 = FindConnectedComponent(vertex1, &disjoint_set);
    Vertex root2 = FindConnectedComponent(vertex2, &disjoint_set);

    if (root1 == root2) {
      continue;
    }

    // This edge can be added, add an edge in either direction with
    // the same weight as the original graph.
    const double edge_weight = graph.EdgeWeight(vertex1, vertex2);
    forest->AddEdge(vertex1, vertex2, edge_weight);
    forest->AddEdge(vertex2, vertex1, edge_weight);

    // Connected the two connected components by updating the
    // disjoint_set structure. Always connect the connected component
    // with the greater index with the connected component with the
    // smaller index. This should ensure shallower trees, for quicker
    // lookup.
    if (root2 < root1) {
      std::swap(root1, root2);
    }

    disjoint_set[root2] = root1;
  }
  return forest;
}

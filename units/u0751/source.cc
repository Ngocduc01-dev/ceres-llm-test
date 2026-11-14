// u0751 – ceres::internal::OrderingToGroupSizes
// Trích từ internal/ceres/parameter_block_ordering.cc, dòng 162–177 (chỉ để xem, không compile)

void OrderingToGroupSizes(const ParameterBlockOrdering* ordering,
                          std::vector<int>* group_sizes) {
  CHECK(group_sizes != nullptr);
  group_sizes->clear();
  if (ordering == nullptr) {
    return;
  }

  // TODO(sameeragarwal): Investigate if this should be a set or an
  // unordered_set.
  const std::map<int, std::set<double*>>& group_to_elements =
      ordering->group_to_elements();
  for (const auto& g_t_e : group_to_elements) {
    group_sizes->push_back(g_t_e.second.size());
  }
}

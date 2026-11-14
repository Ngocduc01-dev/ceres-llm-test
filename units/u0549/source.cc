// u0549 – ceres::internal::CheckForDuplicates
// Trích từ internal/ceres/covariance_impl.cc, dòng 72–99 (chỉ để xem, không compile)

template <typename T>
void CheckForDuplicates(std::vector<T> blocks) {
  std::sort(blocks.begin(), blocks.end());
  auto it = std::adjacent_find(blocks.begin(), blocks.end());
  if (it != blocks.end()) {
    // In case there are duplicates, we search for their location.
    std::map<T, std::vector<int>> blocks_map;
    for (int i = 0; i < blocks.size(); ++i) {
      blocks_map[blocks[i]].push_back(i);
    }

    std::ostringstream duplicates;
    while (it != blocks.end()) {
      duplicates << "(";
      for (int i = 0; i < blocks_map[*it].size() - 1; ++i) {
        duplicates << blocks_map[*it][i] << ", ";
      }
      duplicates << blocks_map[*it].back() << ")";
      it = std::adjacent_find(it + 1, blocks.end());
      if (it < blocks.end()) {
        duplicates << " and ";
      }
    }

    LOG(FATAL) << "Covariance::Compute called with duplicate blocks at "
               << "indices " << duplicates.str();
  }
}
